from TwitterAPI import TwitterAPI
from threading import *
import json
import serial
import time
import sys

ckey = 'YOUR-CONSUMER-KEY'
csecret = 'YOUR-CONSUMER-SECRET-KEY'
atoken = 'YOUR-ACCESS-TOKEN'
asecret = 'YOUR-ACCESS-TOKEN-SECRET'
specialchar = {'é' : 'e', 'è' : 'e', 'ê' : 'e', 'ë' : 'e',
               'à' : 'a', 'â' : 'a', 'ä' : 'a',
               'ü' : 'u', 'û' : 'u', 'ù' : 'u', 'î' : 'i', 'ï' : 'i',
               'ç' : 'c', 'ô' : 'o', 'ö' : 'o', 'œ' : 'oe',
               'É' : 'E', 'È' : 'E', 'Ê' : 'E', 'Ë' : 'E',
               'À' : 'A', 'Â' : 'A', 'Ä' : 'A',
               'Œ' : 'OE', 'Ù' : 'U', 'Ü' : 'U', 'Û' : 'U',
               '«' : '\"', '»' : '\"', '…' : '...'}

api = TwitterAPI(ckey, csecret, atoken, asecret)
check = False

def print_char(ser, s, i):
    if not replace_char(s[i], ser):
        ser.write(bytes(s[i], 'ISO8859-1', 'replace'))
    if i % 50 == 0:
        time.sleep(0.5)
    else:
        time.sleep(0.05)

def print_str(ser, s):
    i = 0
    for c in s:
        print_char(ser, s, i)
        i += 1

def replace_char(c, ser):
    try:
        print_str(ser, specialchar[c]);
        return True
    except KeyError:
        return False
    except Exception as e:
        print('\n\n**********************\n')
        print('ERROR : ' + str(e))
        print('\n**********************\n\n')
        return False

def print_header(ser):
    ser.write(bytes('\r', 'ISO8859-1'))


def get_data():
    r = ''
    try:
        r = api.request('search/tweets', {'q':'@epitechtoulouse', 'count':'100'})
    except Exception as e:
       time.sleep(1) 
       get_data()
    tweets = []
    i = 0
    j = 0
    for item in r:
        item['text'].encode("utf-8", errors='ignore')
        if item['text'][0:2] != 'RT':
            tweets.append(item['text'])
            j += 1
        i += 1
    return tweets

def read_minitel(ser):
    recv = ser.read()
    try:
        recv = recv.decode('UTF-8')
    except:
        pass
    return recv
    

def push_data(ser, cond):
    tweet = str()
    while (True):
        time.sleep(0.05)
        recv = ser.read()
        if recv != -1:
            cond.acquire()
            check = True
            print_header(ser)
            print_str(ser, 'Votre tweet (140 max) : ')
            tweeting = True
            i = 0
            while tweeting:
                recv = read_minitel(ser)
                if recv == b'\x93':
                    time.sleep(0.05)
                    recv = read_minitel(ser)
                    if recv == 'A':
                        r = api.request('statuses/update', {'status':tweet})
                        print(r.status_code)
                        print('Votre tweet : ' + tweet)
                        tweet = ""
                        tweeting = False
                    if recv == 'G':
                        tweet = tweet[0:len(tweet) - 1]
                        i -= 1
                        print_str(ser, '\a');
                    if recv == 'E':
                        tweet = ""
                        tweeting = False
                else:
                    tweet += str(recv)
                    i += 1
            cond.notify()
            check = False
            print_header(ser)
            cond.release()

def print_data(ser, tweets, ad, cond):
    for i in range(3):
        try:
            tweets[i + ad]
        except IndexError:
            break
        except Exception as e:
            print ('Error : ' + str(e))
        tweets[i + ad] = '\n\n' + tweets[i + ad]
        j = 0
        while j < len(tweets[i + ad]):
            cond.acquire()
            if check == True:
                cond.wait()
                j = 0
            cond.release()
            print_char(ser, tweets[i + ad], j)
            j += 1
        print_str(ser, '\n\n')
        time.sleep(3)
    print_header(ser)

def print_loop(ser, cond):
    i = 0
    tweets = get_data()
    while (True):
        if len(tweets) < i + 3:
            tweets = get_data()
            i = 0
        print_data(ser, tweets, i, cond)
        i += 3


def main():
    print('START - ' + time.strftime("%d-%m-%Y %H:%M"))
    ser = serial.Serial('/dev/ttyACM0', 4800)
    cond = Condition()
    printLoop = Thread(None, print_loop, None, (ser, cond))
    writeLoop = Thread(None, push_data, None, (ser, cond))
    writeLoop.start()
    printLoop.start()
    writeLoop.join()
    printLoop.join()

if (__name__ == '__main__'):
    main()
