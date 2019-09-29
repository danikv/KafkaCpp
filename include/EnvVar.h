/*
 * env_var.h
 *
 *  Created on: 29 Sep 2019
 *      Author: danielk
 */

#ifndef INCLUDE_ENVVAR_H_
#define INCLUDE_ENVVAR_H_
#include <string>

namespace Env
{

	template<typename T>
	T getEnv(const std::string& name, T default_value)
	{
		std::string env = std::getenv(name.c_str());
		if(env.empty())
			return default_value;
		return T{env};
	}

	template<>
	int getEnv(const std::string& name, int default_value)
	{
		std::string env = std::getenv(name.c_str());
		if(env.empty())
			return default_value;
		return std::atoi(env.c_str());
	}

}


#endif /* INCLUDE_ENVVAR_H_ */
