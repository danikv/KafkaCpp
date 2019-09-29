/*
 * Events.cpp
 *
 *  Created on: 29 Sep 2019
 *      Author: danielk
 */

#include "Events.h"

#include <iostream>

namespace Events {

void ExampleEventCb::event_cb (RdKafka::Event& event)
{

  switch (event.type())
  {
//    case RdKafka::Event::EVENT_ERROR:
//      if (event.fatal()) {
//        std::cerr << "FATAL ";
//        run = false;
//      }
//      std::cerr << "ERROR (" << RdKafka::err2str(event.err()) << "): " <<
//          event.str() << std::endl;
//      break;
//
//    case RdKafka::Event::EVENT_STATS:
//      std::cerr << "\"STATS\": " << event.str() << std::endl;
//      break;
//
//    case RdKafka::Event::EVENT_LOG:
//      fprintf(stderr, "LOG-%i-%s: %s\n",
//              event.severity(), event.fac().c_str(), event.str().c_str());
//      break;
//
//    case RdKafka::Event::EVENT_THROTTLE:
//	std::cerr << "THROTTLED: " << event.throttle_time() << "ms by " <<
//	  event.broker_name() << " id " << (int)event.broker_id() << std::endl;
//	break;

    default:
      std::cerr << "EVENT " << event.type() <<
          " (" << RdKafka::err2str(event.err()) << "): " <<
          event.str() << std::endl;
      break;
  }
}
void ExampleRebalanceCb::rebalance_cb (RdKafka::KafkaConsumer *consumer, RdKafka::ErrorCode err,
		  std::vector<RdKafka::TopicPartition*> &partitions)
{
	std::cerr << "RebalanceCb: " << RdKafka::err2str(err) << ": ";
}

} /* namespace Events */
