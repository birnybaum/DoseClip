# -*- coding: utf-8 -*-
"""
Created on Sun Feb 12 14:01:52 2023

@author: birnb
"""

import numpy as np
import matplotlib.pyplot as plt
import datetime
import time 


samples_per_second=12

#def get_time():
date_time = datetime.datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
hours=datetime.datetime.now().strftime("%H")
minutes=datetime.datetime.now().strftime("%M")
seconds=datetime.datetime.now().strftime("%S")
print(hours+' hours')
print(minutes+' minutes')
print(seconds+' seconds')
   # return


#def get_dB():
    #this is where you would use a microphone to get external dB data
dB_gen= np.random.randint(80,125)
    #dB_gen = np.average(givenArray.reshape(-1, 12), axis=1).astype(float)          
    #print((dB_gen),'dB')
#%%
#get_dB()
#get_time()
dB=[]
print(dB)
sec=datetime.datetime.now()
print(sec)
#%%
x=[80,85,90,95,100,105,110,115] #dB sound level
y=[1920,960,480,240,120,60,30,15] #time in minutes
plt.figure(figsize=(12,10))
p=np.polyfit(x, np.log(y), 1)
a = np.exp(p[1])
b = p[0]
x_fitted = np.linspace(np.min(x), np.max(x), 100)
y_fitted = a * np.exp(b * x_fitted)

ax = plt.axes()
ax.scatter(y, x, label='Exchange Rate')
ax.plot(y_fitted, x_fitted, 'k', label='Fitted curve')
ax.set_title('Fitting an Exponential Function for dB Exchange Rate') #Max Healthy 
ax.set_xlabel('Time (minutes)')
ax.set_ylabel('Noise Level (dB)')
ax.legend()

#SHOW 
p
#%%

#delta = datetime.timedelta(hours = int(hours),minutes = int(minutes),seconds = int(seconds))
#delta = datetime.timedelta(hours =10,minutes = 0,seconds =0)
#collectedtime = datetime.datetime.now().strftime("%H:%M:%S")
#difference = delta - int(collectedtime)
#if dB_gen >= 100:
 #   delta   
  #  print(delta)
  
seconds = 0
AVG_dB=[]
Time=1 #This will be 1 for 1 minute
Allowance_Start=100#Allowance Will start at 100%
print(round(Allowance_Start),'% Start Allowance for Day')
while (seconds<24):
       dB=[] 
       for x in range(12):
           dB.append(np.random.randint(80,125)) #going to be dB values from SLM
       print(dB)
       seconds = seconds + 1 
       time.sleep(1)
       AVG=np.mean(dB)
       print(AVG)
       Allowance_Start=Allowance_Start-(100*Time*(1/(np.exp(p[0]*AVG)*np.exp(p[1]))))
       if Allowance_Start > 60:
           print(round(Allowance_Start),'% Remaining, Healthy Enviornment')
       elif Allowance_Start>10:
           print(round(Allowance_Start),'% Remaining, Be Careful go to Quieter Enviornment')
       elif Allowance_Start>0:
           print(round(Allowance_Start),'% Remaining, Limit Reached, Risk for Hearing Loss!')
       else:
           print(round(abs(Allowance_Start)),'% Over Limit, Danger for Hearing Loss!')
      # AVG_dB= AVG_dB+[AVG]     
#print(AVG_dB, 'dBA')
       



#%%
Time=1 #This will be 1 for 1 minute
Allowance_Start=100 #Allowance Will start at 100%


print(round(Allowance_Start),'% Start Allowance for Day')
for num in AVG_dB:
    Allowance_Start=Allowance_Start-(100*Time*(1/(np.exp(p[0]*num)*np.exp(p[1]))))
    if Allowance_Start > 60:
        print(round(Allowance_Start),'% Remaining, Healthy Enviornment')
    elif Allowance_Start>10:
        print(round(Allowance_Start),'% Remaining, Be Careful go to Quieter Enviornment')
    elif Allowance_Start>0:
        print(round(Allowance_Start),'% Remaining, Limit Reached, Risk for Hearing Loss!')
    else:
        print(round(abs(Allowance_Start)),'% Over Limit, Danger for Hearing Loss!')
 