#include <iostream>
#include "data.proto2.pb.h"
int main()
{
	std::cout << "ProtobufDemo" << std::endl;
	data::User *user = new data::User();
	user->set_name("protobuf");
	std::cout << user->name() << std::endl;
	return 0;
}