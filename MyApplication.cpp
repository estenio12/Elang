// # Code generated by Elang Compiler
// # Licensed under Apache 2.0
#include<bits/stdc++.h>
std::string floatToStr(float __elang_param){return std::to_string(__elang_param);}std::string intToStr(int __elang_param){return std::to_string(__elang_param);}
std::string boolToStr(bool __elang_param){return (__elang_param==false) ? "false" : "true";}
int floatToInt(float __elang_param){return static_cast<int>(__elang_param);}float intToFloat(int __elang_param){return static_cast<float>(__elang_param);}
int strToInt(std::string __elang_param){if(__elang_param.empty()){std::cerr<<"\nData Format error: cannot convert empty string to integer\n";exit(EXIT_FAILURE);}return std::stoi(__elang_param);}
float strToFloat(std::string __elang_param){if(__elang_param.empty()){std::cerr<<"\nData Format error: cannot convert empty string to float\n";exit(EXIT_FAILURE);}return std::stof(__elang_param);}
bool strToBool(std::string __elang_param){if(__elang_param.empty()){std::cerr<<"\nData Format error: cannot convert empty string to boolean\n";exit(EXIT_FAILURE);}return (__elang_param=="false"||__elang_param=="0") ? false : true;}
class __elang_class_runnable_cxx{private:public:__elang_class_runnable_cxx();~__elang_class_runnable_cxx();public:void __elang_run_body_cxx();private:};
__elang_class_runnable_cxx::__elang_class_runnable_cxx(){}__elang_class_runnable_cxx::~__elang_class_runnable_cxx(){}void __elang_class_runnable_cxx::__elang_run_body_cxx(){std::cout<<floatToInt(65.76)<<"\n";std::cout<<strToInt("34")<<"\n";std::cout<<strToFloat("78.32")<<"\n";std::cout<<strToBool("false")<<"\n";std::cout<<floatToStr(93.233)<<"\n";std::cout<<intToStr(52)<<"\n";std::cout<<boolToStr(true)<<"\n";std::cout<<intToFloat(22)<<"\n";}
int main(int argc, char* argv[]){auto startup=new __elang_class_runnable_cxx();startup->__elang_run_body_cxx();return EXIT_SUCCESS;}