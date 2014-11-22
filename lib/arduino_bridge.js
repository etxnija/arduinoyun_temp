var request = require('request');

module.exports = {

tempCall: function tempCall(callback) {
		request('http://arduino.local/arduino/tempF', function (error, response, body) {
		  if (!error && response.statusCode == 200) {
		    var temp = body.trim();
		    callback(null, temp);
		  }
		})
	},

humidityCall: function humidityCall(callback) {
		request('http://arduino.local/arduino/humidity', function (error, response, body) {
		  if (!error && response.statusCode == 200) {
		    var humidity = body.trim();
		    callback(null, humidity);
		  }
		})
	}
};