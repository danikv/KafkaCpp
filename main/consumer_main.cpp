/*
 * consumer_main.cpp
 *
 *  Created on: 29 Sep 2019
 *      Author: danielk
 */

#include "KafkaConsumer.h"
#include <iostream>

int main (int argc, char **argv) {
	std::cout << "Hello World";
	KafkaConsumer consumer{{"bla", "bla2"}};
	std::cout << "consumer created" << std::endl;
}

