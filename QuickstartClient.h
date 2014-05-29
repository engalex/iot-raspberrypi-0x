
#include "mqtt/async_client.h"
#include <iostream>
#include <string>

class QuickstartClient {
private:
	const long TIMEOUT = 10000L;
	std::string topic, myName;
	mqtt::async_client* client;
	mqtt::itoken_ptr connectionToken;

	class ClientCallback : public virtual mqtt::callback {
		virtual void connection_lost(const std::string& cause);
		virtual void delivery_complete(mqtt::idelivery_token_ptr tok);
		virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg);
	};

	void connect(void);
	void disconnect(void);
public:
	QuickstartClient(std::string deviceName, std::string macAddress);
	~QuickstartClient(void);
	void publish(double cpuTemperature, double cpuLoad, double sine);
};