#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <istream>
#include <ostream>
#include <boost/lexical_cast.hpp>

#include "icmp_header.hpp"
#include "ipv4_header.hpp"
#include "MyPing.h"




using boost::asio::ip::icmp;
using boost::asio::steady_timer;
namespace chrono = boost::asio::chrono;


class MyPinger : public Debug {
public:
	MyPinger(boost::asio::io_context& io_context,const char* ipAdress)
		: m_ipAdress(ipAdress),
		Debug(true,false,"class Mypinger"),
		resolver_(io_context), socket_(io_context, icmp::v4()),
		timer_(io_context), sequence_number_(0), num_replies_(0)
	{
		//Debug deb(true, false, "class MyPinger");
		msg("MyPinger constructed.");
		testAccess();

		destination_ = *resolver_.resolve(icmp::v4(), ipAdress, "").begin();

		startSend();
		startReceive();
	}

	friend class ImplementMyPing;
private:
	void startSend() {
		std::string body("\"Hello!\" from Asio ping.");

		// Create an ICMP header for an echo request.
		icmp_header echo_request;
		echo_request.type(icmp_header::echo_request);
		echo_request.code(0);
		echo_request.identifier(get_identifier());
		echo_request.sequence_number(++sequence_number_);
		compute_checksum(echo_request, body.begin(), body.end());

		// Encode the request packet.
		boost::asio::streambuf request_buffer; //the data get put into request_buffer, first echo_request, then body, and checksum is saved beforehand from both parts as whole.
		std::ostream os(&request_buffer);
		os << echo_request << body;

		// Send the request.
		time_sent_ = steady_timer::clock_type::now();
		socket_.send_to(request_buffer.data(), destination_);

		// Wait up to five seconds for a reply.
		msg("start timer");
		num_replies_ = 0;
		timer_.expires_at(time_sent_ + chrono::seconds(5));


		timer_.async_wait(boost::bind(&MyPinger::handleTimeout, this));
		msg("at the end of startSend()");
	}

	//we have sent the data package
	//now we need start receive to get it back.

	void startReceive() {
		msg("in startReceive");
		// Discard any data already in the buffer.
		reply_buffer_.consume(reply_buffer_.size());

		// Wait for a reply. We prepare the buffer to receive up to 64KB.
		socket_.async_receive(reply_buffer_.prepare(65536),
			boost::bind(&MyPinger::handleReceive, this, _2));
	}

	void handleTimeout() {
		msg("in handleTimeout");
		if (num_replies_ == 0)
			msg( "Request timed out" );

		// Requests must be sent no less than one second apart.
		timer_.expires_at(time_sent_ + chrono::seconds(1));
		timer_.async_wait(boost::bind(&MyPinger::startSend, this));
	}

	void handleReceive(std::size_t length) {
		msg("in handleReceive");
		// The actual number of bytes received is committed to the buffer so that we
		// can extract it using a std::istream object.
		reply_buffer_.commit(length);

		// Decode the reply packet.
		std::istream is(&reply_buffer_);
		ipv4_header ipv4_hdr;
		icmp_header icmp_hdr;
		is >> ipv4_hdr >> icmp_hdr;

		// We can receive all ICMP packets received by the host, so we need to
		// filter out only the echo replies that match the our identifier and
		// expected sequence number.
		if (is && icmp_hdr.type() == icmp_header::echo_reply
			&& icmp_hdr.identifier() == get_identifier()
			&& icmp_hdr.sequence_number() == sequence_number_)
		{
			// If this is the first reply, interrupt the five second timeout.
			if (num_replies_++ == 0)
				timer_.cancel();

			// Print out some information about the reply packet.
			chrono::steady_clock::time_point now = chrono::steady_clock::now();
			chrono::steady_clock::duration elapsed = now - time_sent_;
			/*std::cout << length - ipv4_hdr.header_length()
				<< " bytes from " << ipv4_hdr.source_address()
				<< ": icmp_seq=" << icmp_hdr.sequence_number()
				<< ", ttl=" << ipv4_hdr.time_to_live()
				<< ", time="
				<< chrono::duration_cast<chrono::milliseconds>(elapsed).count()
				<< std::endl;
			*/
			msg("try to put all the info into msg:\n");
			//bytes:
			msg(boost::lexical_cast<std::string>(length - ipv4_hdr.header_length())+" bytes");
			//from:
			msg("from:"+boost::lexical_cast<std::string>(ipv4_hdr.source_address()));
			//icmp_seq:
			msg("icmp_seq="+boost::lexical_cast<std::string>(icmp_hdr.sequence_number()));
			//ttl=
			msg("ttl="+boost::lexical_cast<std::string>(ipv4_hdr.time_to_live()));
			//time elapsed:
			msg("time elapsed: "+boost::lexical_cast<std::string>(chrono::duration_cast<chrono::milliseconds>(elapsed).count()));

		}
		startReceive();
		msg("end of handleReceive");
		readLog();
	}

private:
	//Debug deb;
	void testAccess() { 
		msg("testAccess working."); }
	const char* m_ipAdress;

private:
	//the boost example variables
	icmp::resolver resolver_;
	icmp::endpoint destination_;
	icmp::socket socket_;
	steady_timer timer_;
	unsigned short sequence_number_;
	chrono::steady_clock::time_point time_sent_;
	boost::asio::streambuf reply_buffer_;
	std::size_t num_replies_;

	static unsigned short get_identifier()
	{
#if defined(BOOST_ASIO_WINDOWS)
		return static_cast<unsigned short>(::GetCurrentProcessId());
#else
		return static_cast<unsigned short>(::getpid());
#endif
	}


};

std::string ImplementMyPing::runPing() {
	std::string pingResult = "did not ping";

	msg("in runPing.");

	boost::asio::io_context io;
	MyPinger p(io, m_ipAdress);
	io.run_one();
	msg("after io.run_one()");
	addToLog(p.getLog());
	readLog();
	return pingResult;
}


/*
class pinger
{
public:
pinger(boost::asio::io_context& io_context, const char* destination)
: resolver_(io_context), socket_(io_context, icmp::v4()),
timer_(io_context), sequence_number_(0), num_replies_(0)
{
destination_ = *resolver_.resolve(icmp::v4(), destination, "").begin();

//boost::asio::signal_set signals(io_context, SIGINT);
start_send();
start_receive();
}

private:

void start_send()
{
std::string body("\"Hello!\" from Asio ping.");

// Create an ICMP header for an echo request.
icmp_header echo_request;
echo_request.type(icmp_header::echo_request);
echo_request.code(0);
echo_request.identifier(get_identifier());
echo_request.sequence_number(++sequence_number_);
compute_checksum(echo_request, body.begin(), body.end());

// Encode the request packet.
boost::asio::streambuf request_buffer;
std::ostream os(&request_buffer);
os << echo_request << body;

// Send the request.
time_sent_ = steady_timer::clock_type::now();
socket_.send_to(request_buffer.data(), destination_);

// Wait up to five seconds for a reply.
num_replies_ = 0;
timer_.expires_at(time_sent_ + chrono::seconds(5));

//custom conditional code: limit pings via ending the second loop
if (m_limit_pings > 1)
timer_.async_wait(boost::bind(&pinger::handle_timeout, this));
}

void handle_timeout()
{
if (num_replies_ == 0)
std::cout << "Request timed out" << std::endl;

// Requests must be sent no less than one second apart.
timer_.expires_at(time_sent_ + chrono::seconds(1));
timer_.async_wait(boost::bind(&pinger::start_send, this));
}

void start_receive()
{
// Discard any data already in the buffer.
reply_buffer_.consume(reply_buffer_.size());

// Wait for a reply. We prepare the buffer to receive up to 64KB.
socket_.async_receive(reply_buffer_.prepare(65536),
boost::bind(&pinger::handle_receive, this, _2));
}

void handle_receive(std::size_t length)
{
// The actual number of bytes received is committed to the buffer so that we
// can extract it using a std::istream object.
reply_buffer_.commit(length);

// Decode the reply packet.
std::istream is(&reply_buffer_);
ipv4_header ipv4_hdr;
icmp_header icmp_hdr;
is >> ipv4_hdr >> icmp_hdr;

// We can receive all ICMP packets received by the host, so we need to
// filter out only the echo replies that match the our identifier and
// expected sequence number.
if (is && icmp_hdr.type() == icmp_header::echo_reply
&& icmp_hdr.identifier() == get_identifier()
&& icmp_hdr.sequence_number() == sequence_number_)
{
// If this is the first reply, interrupt the five second timeout.
if (num_replies_++ == 0)
timer_.cancel();

// Print out some information about the reply packet.
chrono::steady_clock::time_point now = chrono::steady_clock::now();
chrono::steady_clock::duration elapsed = now - time_sent_;
std::cout << length - ipv4_hdr.header_length()
<< " bytes from " << ipv4_hdr.source_address()
<< ": icmp_seq=" << icmp_hdr.sequence_number()
<< ", ttl=" << ipv4_hdr.time_to_live()
<< ", time="
<< chrono::duration_cast<chrono::milliseconds>(elapsed).count()
<< std::endl;
}
if (m_limit_pings > 1) {
//Da dies nicht den eigentlichen ping beendet ist es als Lösung ungeeignet, und wieder von mir zurück gesetzt.
//Nach dem 4. Ping kommt es dann zu der Nachricht "Request Timeout" - wir haben nämlich keine Schleife,
//sonder einen Thread am laufen der anscheinend (laut einem Forennutzer) nur mit einem Signal beendet werden kann.
//Neuerung: Dies war der richtige Ort um die Schleife zu beenden, nur gab es noch eine zweite Schleife weiter oben.
start_receive();
m_limit_pings--;

}
else {
std::cout << "here we should stop\n";
//doesnt give an error but doesnt work either:
//boost::asio::io_context stop();
}


//start_receive();

}

//Von mir eingefügt, hat aber keine Funktion mehr.
short m_limit_pings = 4;
//boost::asio::signal_set* m_signal;

static unsigned short get_identifier()
{
#if defined(BOOST_ASIO_WINDOWS)
return static_cast<unsigned short>(::GetCurrentProcessId());
#else
return static_cast<unsigned short>(::getpid());
#endif
}


icmp::resolver resolver_;
icmp::endpoint destination_;
icmp::socket socket_;
steady_timer timer_;
unsigned short sequence_number_;
chrono::steady_clock::time_point time_sent_;
boost::asio::streambuf reply_buffer_;
std::size_t num_replies_;
};
*/