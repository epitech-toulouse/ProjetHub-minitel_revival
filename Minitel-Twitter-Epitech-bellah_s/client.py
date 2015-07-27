from tweepy import Stream
from tweepy import OAuthHandler
from tweepy.streaming import StreamListener
import json
import serial
import time
import sys

ckey = 'uOgd4dBygOguORWftJCwJfZoR'
csecret = 'Y3rIpPUhFUqkjPffKEd9qcZf71sHDmDjvZUgqSwAQUjc7DXano'
atoken = '96362656-RxcZN4PCbE4PLM5EJTtajqhVhsf36WjrVjonCJYq8'
asecret = 'PPqdkq6sDIi3xmXKsYBUr2fdfwAcKLkJx5KTlOX0KElbB'

class listener(StreamListener):
    def on_data(self, data):
        ser = serial.Serial('/dev/tty.usbmodem1421', 4800)
        tweets = json.loads(data)
        text = tweets['text']
        print(text)
        print("Tweet send")
        i = 0
        for c in text: 
            ser.write(bytes('' + c, 'ISO8859-1', 'replace'))
            if i % 15 == 0:
                time.sleep(1)
            else:
                time.sleep(0.003)
            i += 1
        ser.write(bytes('\n', 'ISO8859-1'))
        ser.write(bytes('\n', 'ISO8859-1'))
        time.sleep(5)
    def on_error(self, status):
        print (status)


auth = OAuthHandler(ckey, csecret)
auth.set_access_token(atoken, asecret)
twitterStream = Stream(auth, listener())
twitterStream.filter(track=["France"])