import CppHeaderParser
import os
from jinja2 import Environment, Template, PackageLoader, select_autoescape
from .cci_helpers import cci_sanitize_rettype, cci_sanitize_func_name, cci_get_output_arguments




DOCS_TEMPLATE = """
/*
 * Class:     {{ package_name }}
 * Method:    {{"JNI_" if include_jni_in_method_name}}{{ method_name }}
 * Signature: ({{args_abbrv}}){{retrn_abbr}}
 */
{{ return_type }} {{full_method_name}}
  (JNIEnv *, jclass{{ jni_func_args }})
{
{{ function_body }}
}

"""


class JniGenerator():
    def __init__(self, definition):
        self.jni_package_name = "Java_%s_" % definition.jni_package
        self.jni_prefix = "Java_%s_" % definition.jni_package
        self.include_jni_in_method_name = definition.include_jni_in_method_name
        self.doc_package_name = definition.jni_package
        self.full_jni_prefix = "Java_%s" % definition.full_jni_package
        self.cci_prefix = definition.cci_prefix           
        self.getter_overrides = definition.cci_getter_overrides
        self.conversion_function = definition.cci_conversion_function

    def __load_cci_functions(self, header_file):
        parsed_header = CppHeaderParser.CppHeader(header_file)
        
        jni_functions = {}
        for func in parsed_header.functions:
            jni_functions[func["name"][len(self.cci_prefix):]] = func
    #         print(func.keys())
    #         print(" %s"%func["name"])
    #         print(" %s"%func["doxygen"])
    #     print("\n".join(jni_functions))
    
        return jni_functions

    def __get_setter_function_body(self, cci_func, jni_func):
        output = ""
        
#         print("FFFFF", jni_func['rtnType'])
        if 'ctre::phoenix::ErrorCode' in cci_func['rtnType'] and "void" not in jni_func['rtnType']:
            output += "    return (jint)"
        else:
            output += "    "
            
        output += cci_func['name'] + "(%s(handle)" % self.conversion_function
        
        for arg in cci_func['parameters']:
            if arg['name'] != 'handle':
                output += ", " + arg['name']
        
        output += ");"
        
        return output
    
    
    def __get_getter_function_body(self, cci_func, output_arguments):
        
        default_value = {}
        default_value["bool *"] = " = false"
        default_value["const char *"] = ""
        default_value["int *"] = " = 0"
        default_value["double *"] = " = 0"
        default_value["size_t *"] = " = 0"
        default_value["ctre::phoenix::motorcontrol::MotorCommutation *"] = " "
        default_value["const double *"] = " = 0"
        default_value["char *"] = " = 0"
        default_value["ctre::phoenix::sensors::MagnetFieldStrength *"] = " = 0"
        default_value["ctre::phoenix::sensors::SensorVelocityMeasPeriod *"] = " = 0"
        default_value["ctre::phoenix::sensors::AbsoluteSensorRange *"] = " = 0"
        default_value["ctre::phoenix::sensors::SensorInitializationStrategy *"] = " = 0"
        default_value["ctre::phoenix::sensors::SensorTimeBase *"] = " = 0"
        
        output = ""
        
        for arg in cci_func['parameters']:
            if str(arg['name']) in output_arguments:
                output += "    " + arg['type'].replace(" *", "") + " " + arg['name'] + default_value[str(arg['type'])] + ";\n"
            
        output += "    "
        output += cci_func['name'] + "(%s(handle)" % self.conversion_function
        
        for arg in cci_func['parameters']:
            if arg['name'] != 'handle':
                if "*" in arg['type'] and arg['type'] != "void *":
                    output += ", &" + arg['name']
                else:
                    output += ", " + arg['name']
        
        output += ");\n"
        
        for arg in cci_func['parameters']:
            if "*" in arg['type'] and arg['type'] != "void *":
                output += "    return " + arg['name'] + ";"
                break
        
        return output
    
    
    def __sanitize_jni_func_name(self, func):
        sanitized_func_name = func["name"][len(self.full_jni_prefix):]
#         print("Sanitizing ", func['name'], sanitized_func_name, "\t", self.full_jni_prefix)
    #     sanitized_func_name = sanitized_func_name.replace("Create", "Create1")
        sanitized_func_name = sanitized_func_name.replace("Config_1", "Config_")
        sanitized_func_name = sanitized_func_name.replace("JNI_1destroy_1MotController", "Destroy")
        sanitized_func_name = sanitized_func_name.replace("Set_14", "Set_4")
        sanitized_func_name = sanitized_func_name.replace("SetInverted_12", "SetInverted_2")
        sanitized_func_name = sanitized_func_name.replace("GetActiveTrajectoryPosition3", "GetActiveTrajectoryPosition_3")
        sanitized_func_name = sanitized_func_name.replace("GetActiveTrajectoryVelocity3", "GetActiveTrajectoryVelocity_3")
        sanitized_func_name = sanitized_func_name.replace("GetActiveTrajectoryArbFeedFwd3", "GetActiveTrajectoryArbFeedFwd_3")
        sanitized_func_name = sanitized_func_name.replace("PushMotionProfileTrajectory2", "PushMotionProfileTrajectory_2")
        sanitized_func_name = sanitized_func_name.replace("PushMotionProfileTrajectory3", "PushMotionProfileTrajectory_3")
        sanitized_func_name = sanitized_func_name.replace("GetMotionProfileStatus2", "GetMotionProfileStatus_2")
        sanitized_func_name = sanitized_func_name.replace("ConfigPulseWidthPeriod_1EdgesPerRot", "ConfigPulseWidthPeriod_EdgesPerRot")
        sanitized_func_name = sanitized_func_name.replace("ConfigPulseWidthPeriod_1FilterWindowSz", "ConfigPulseWidthPeriod_FilterWindowSz")
    #     sanitized_func_name = sanitized_func_name.replace("ConfigBrakeCurrentLimit", "ConfigBrakeCurrentLimit")
    #     sanitized_func_name = sanitized_func_name.replace("ConfigBrakeCurrentLimitEnable", "ConfigBrakeCurrentLimitEnable")
    #     sanitized_func_name = sanitized_func_name.replace("GetIntegratedSensorPosition", "GetIntegratedSensorPosition")
    #     sanitized_func_name = sanitized_func_name.replace("GetIntegratedSensorAbsolutePosition", "GetIntegratedSensorAbsolutePosition")
    #     sanitized_func_name = sanitized_func_name.replace("GetIntegratedSensorVelocity", "GetIntegratedSensorVelocity")
    #     sanitized_func_name = sanitized_func_name.replace("ConfigAbsoluteSensorRange", "ConfigAbsoluteSensorRange")
    #     sanitized_func_name = sanitized_func_name.replace("ConfigMagnetOffset", "ConfigMagnetOffset")
    #     sanitized_func_name = sanitized_func_name.replace("ConfigSensorInitializationStrategy", "ConfigSensorInitializationStrategy")
        
        return sanitized_func_name
    
    def generate(self, jni_header_file, cci_header_file, template_file, output_file):
        
        output = ""
        
        jni_type_to_abbr_lookup = {}
        jni_type_to_abbr_lookup['int'] = 'I'
        jni_type_to_abbr_lookup['jint'] = 'I'
        jni_type_to_abbr_lookup['jlong'] = 'J'
        jni_type_to_abbr_lookup['jstring'] = 'java/lang/String;'
        jni_type_to_abbr_lookup['jdouble'] = 'D'
        jni_type_to_abbr_lookup['jboolean'] = 'Z'
        jni_type_to_abbr_lookup['void'] = 'V'
        
        jni_type_to_abbr_lookup['jintArray'] = '[I'
        jni_type_to_abbr_lookup['jdoubleArray'] = '[D'
        jni_type_to_abbr_lookup['jshortArray'] = '[S'
        jni_type_to_abbr_lookup['jbooleanArray'] = '[Z'
        
        cci_functions = self.__load_cci_functions(cci_header_file)
        print(cci_functions.keys())
        
        parsed_header = CppHeaderParser.CppHeader(jni_header_file)
        
        jni_functions = []
        for func in parsed_header.functions:
            sanitized_func_name = self.__sanitize_jni_func_name(func)
    #         print(func.keys())
            arg_abbrv = "".join(jni_type_to_abbr_lookup[arg['type']] for arg in func['parameters'] if arg['type'] != "JNIEnv *" and arg['type'] != "jclass")
            
            jni_args = [arg['type'] for arg in func['parameters'] if arg['type'] != "JNIEnv *" and arg['type'] != "jclass"]
            cci_func = cci_functions.get(sanitized_func_name, None)
            cci_args = cci_func['parameters'] if cci_func else []
            if not cci_func:
                print("Bouncing", sanitized_func_name)
                function_body = '    LOG_UNSUPPORTED_CAN_FUNC("");\n    return 0;'
                jni_func_args = jni_args
            else:
                output_arguments = cci_get_output_arguments(cci_func, self.getter_overrides)
                
                if output_arguments:
                    function_body = self.__get_getter_function_body(cci_func, output_arguments)
                else:
                    function_body = self.__get_setter_function_body(cci_func, func)
        
                jni_func_args = []
                jni_arg_ctr = 0
    #             print(output_arguments)
                for cci_ctr, cci_arg in enumerate(cci_args):
                    if str(cci_arg['name']) not in output_arguments:
                        try:
                            jni_func_args.append("%s %s" % (jni_args[jni_arg_ctr], cci_arg['name']))
                            jni_arg_ctr += 1
                        except:
                            print("UH OH")
                            pass
    #                 print(cci_arg)
    
#     {% for _ in jni_args if jni_args%}, {{jni_args[loop.index0]}} {{cci_args[loop.index0].name}}{% endfor%}
            
            output += Template(DOCS_TEMPLATE).render(
                package_name=self.doc_package_name,
                method_name=sanitized_func_name,
                full_method_name=func['name'],
                retrn_abbr=jni_type_to_abbr_lookup[func['rtnType'].split()[1]],
                args_abbrv=arg_abbrv,
                return_type=func['rtnType'],
                cci_args = cci_args,
                jni_args = jni_args,
                function_body=function_body,
                include_jni_in_method_name=self.include_jni_in_method_name,
                jni_func_args=", " + ", ".join(jni_func_args)
                )
        
        with open(template_file) as f:
            template_text = f.read()
         
        print("Dumping to ", output_file)
        with open(output_file, 'w') as f:
            f.write(Template(template_text).render(functions=output))

        
        
def main():    

    from generator_config_factory import generator_config_factory
    definitions = generator_config_factory()
    project_dir = r'F:\git\FIRST\SnobotSim\CtreSimulator'
    jni_dir = os.path.join(project_dir, r"ctre_source\cci\native\include\ctre\phoenix\jni")
    cci_dir = os.path.join(project_dir, r"ctre_source\cci\native\include\ctre\phoenix\cci")
    output_dir = os.path.join(project_dir, r"src/main/native/cpp/ctre_jni_mocks")

    
    for definition in definitions:
        generator = JniGenerator(definition)

        generator.generate(
            os.path.join(jni_dir, '%s.h' % definition.jni_package), 
            os.path.join(cci_dir, '%s.h' % definition.cci_class_name),
            os.path.join(project_dir, "gen_scripts/jni_templates/%s.txt" % definition.cci_class_name),
            os.path.join(output_dir, definition.jni_class_name),)
    
if __name__ == "__main__":
    main()
