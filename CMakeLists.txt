cmake_minimum_required (VERSION 2.6)

project (Kafka)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(kafkacpp src/KafkaConsumer.cpp src/Events.cpp)

add_executable(Kafka main/consumer_main.cpp)

target_link_libraries (Kafka kafkacpp librdkafka.a librdkafka++.a librdkafka.so.1 librdkafka++.so.1 pthread)
