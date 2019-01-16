# -*- coding: utf-8 -*-
"""
Created on Wed Dec 19 11:38:05 2018

@author: alexl
"""

from lxml import html
import requests
import re
import csv

def game_writer(url):
    
    game_id = url[53:61]
    page = requests.get(url)
    tree = html.fromstring(page.content)
    
    times = tree.xpath('//td[@class="time"]/text()')
    text = tree.xpath('//span[@class="text"]/text()')
    plays = text[33:-6]
    
    #trim whitespace from plays
    plays = [p.strip() for p in plays]
    plays = [p.replace('\n', ' ') for p in plays]
    plays = [re.sub(' +', ' ', p) for p in plays]
    
    #Timeouts, for some reason, contain 2 blank spaces
    times_final = []
    plays_final = []    
    t_idx = 0
    p_idx = 0
    skip = False
    while p_idx != len(plays):
        t = times[t_idx]
        p = plays[p_idx]
        if skip:
            p_idx = p_idx + 1
            skip = False
        else:
            if p:
                times_final.append(t)
                plays_final.append(p)
            else:
                skip = True
            p_idx = p_idx + 1
            t_idx = t_idx + 1
        
    #write to .csv
    with open('rebound_data\\' + game_id + '.csv', mode='w') as file:
        test_writer = csv.writer(file, delimiter=';', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    
        for i in range(len(plays_final)):
            if not 'TEAM' in plays_final[i]:
                dboard = 'defensive rebound'
                oboard = 'offensive rebound'
                leave = 'goes to the bench'
                enter = 'enters the game'
                if dboard in plays_final[i]:    
                            test_writer.writerow([times_final[i], plays_final[i][0:-(len(dboard)+1)], dboard])
                if oboard in plays_final[i]:    
                            test_writer.writerow([times_final[i], plays_final[i][0:-(len(oboard)+1)], oboard])
                if leave in plays_final[i]:    
                            test_writer.writerow([times_final[i], plays_final[i][0:-(len(leave)+1)], leave])
                if enter in plays_final[i]:    
                            test_writer.writerow([times_final[i], plays_final[i][0:-(len(enter)+1)], enter])
    
    #for testing purposes
    print("-----------------------")
    print("testing game on " + game_id)
    for i in range(10):
        print("play at " + times_final[i] + ": " + plays_final[i])
    print ("----------------------")
   
urls = []

urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181106_9lhc.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181109_681u.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181112_fqso.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181121_c2z9.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181124_ddmd.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181130_auzn.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181201_445f.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181205_jdme.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181208_r2pd.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181215_73kh.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181218_fsn3.xml?view=plays')
urls.append('http://www.ubbulls.com/sports/mbkb/2018-19/boxscores/20181221_67fs.xml?view=plays')
for url in urls:
    game_writer(url)
