import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import matplotlib.dates as mdates
from matplotlib import dates as mpl_dates
import numpy as np
from matplotlib.ticker import FormatStrFormatter

#INTERESTED COLUMNS
col_names_pir = ["ts", "data_presenceSensor_3","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_door = ["ts", "data_analogInput_4","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_smart = ["ts", "data_analogInput_3","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_pipe = ["ts", "data_temperatureSensor_0","data_humiditySensor_1"]
#################################################################################################################################################################################################


#IMPORT CSV FILE
pir_bathroom_df= pd.read_csv('pir_7519aca0-6a44-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
#pir_office_df= pd.read_csv('pir_5438cf60-8359-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_hall_df= pd.read_csv('pir_45774d90-8358-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_kitchen_df= pd.read_csv('pir_d334f6b0-6a34-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_bedroom_df= pd.read_csv('pir_de9978c0-6a5f-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_livingroom_df= pd.read_csv('pir_e2a8b950-3191-11ec-a5c0-8f487cf8beb8data.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
door_df= pd.read_csv('door_sensor_3f0e4050-4e0e-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_door, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
#balcony_df= pd.read_csv('door_sensor_fd142060-835b-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_door, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
smart_plug_df= pd.read_csv('smart_plug_data.csv', sep=',',usecols=col_names_smart, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
#water_meter_df= pd.read_csv('water_meter_data.csv', sep=',',usecols=col_names_door, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
water_pipe_df= pd.read_csv('water_pipe_data.csv', sep=',',usecols=col_names_pipe, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
#################################################################################################################################################################################################



#PLOT SENSORS
fig, (ax_bedroom,ax_hall,ax_kitchen,ax_bathroom,ax_livingroom,ax_smart) = plt.subplots(6,1,figsize=(20, 100),sharex=True)
#fig, (ax_water_meter) = plt.subplots(1,1,figsize=(20, 100))
ax_bathroom.plot(pir_bathroom_df["data_presenceSensor_3"])
#ax_office.plot(pir_office_df["data_presenceSensor_3"])
ax_kitchen.plot(pir_kitchen_df["data_presenceSensor_3"])
ax_bedroom.plot(pir_bedroom_df["data_presenceSensor_3"])
ax_livingroom.plot(pir_livingroom_df["data_presenceSensor_3"])
ax_hall.plot(pir_hall_df["data_presenceSensor_3"])
#ax_door.plot(door_df["data_analogInput_4"],color="olive")
#ax_balcony.plot(balcony_df["data_analogInput_4"])
ax_smart.plot(smart_plug_df["data_analogInput_3"],color="lightsalmon")
#ax_water_meter.plot(water_meter_df["data_analogInput_4"])
#ax_water_pipe.plot(water_pipe_df["data_temperatureSensor_0"],color="orange")
#ax_water_pipe.plot(water_pipe_df["data_humiditySensor_1"])
#ax1.plot(pir_bathroom_df["data_temperatureSensor_0"],color="orange")
#ax2.plot(pir_bathroom_df["data_humiditySensor_1"],color="purple")
#################################################################################################################################################################################################



#YLABEL INTEGER
ax_bathroom.yaxis.set_major_locator(MaxNLocator(integer=True))
#ax_office.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_hall.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_kitchen.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_bedroom.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_livingroom.yaxis.set_major_locator(MaxNLocator(integer=True))
#ax_door.yaxis.set_major_locator(MaxNLocator(integer=True))



#ax1.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
#ax2.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
#ax_water_pipe.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
#ax_water_meter.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
#################################################################################################################################################################################################


ax_bathroom.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
ax_hall.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
ax_kitchen.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
ax_bedroom.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
ax_livingroom.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
ax_smart.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
#ax_door.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
#ax1.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
#ax2.xaxis.set_major_locator(mdates.HourLocator(interval = 5))
#ax_water_pipe.xaxis.set_major_locator(mdates.HourLocator(interval = 5))


start_bath, end_bath = ax_bathroom.get_ylim()
start_hall, end_hall = ax_hall.get_ylim()
start_kitchen, end_kitchen = ax_kitchen.get_ylim()
start_bedroom, end_bedroom = ax_bedroom.get_ylim()
start_livingroom, end_livingroom = ax_livingroom.get_ylim()
#start_smart, end_smart = ax_smart.get_ylim()
#start, end = ax1.get_ylim()
#start1, end1 = ax_water_pipe.get_ylim()
#start2, end2 = ax2.get_ylim()


ax_bathroom.yaxis.set_ticks(np.arange(0, end_bath, 4))
ax_hall.yaxis.set_ticks(np.arange(0, end_hall, 4))
ax_kitchen.yaxis.set_ticks(np.arange(0, end_kitchen, 4))
ax_bedroom.yaxis.set_ticks(np.arange(0, end_bedroom, 4))
ax_livingroom.yaxis.set_ticks(np.arange(0, end_livingroom, 4))
ax_smart.yaxis.set_ticks(np.arange(0, 1),0.05)
#ax_water_pipe.yaxis.set_ticks(np.arange(start1, end1, 5))
#ax2.yaxis.set_ticks(np.arange(start2, end2, 9))
#ax1.yaxis.set_ticks(np.arange(start, end, 0.5))




#LABEL ALL SENSORS

ax_bathroom.set_ylabel("Movement")
#ax1.set_ylabel("Temp. [ºc]")
#ax2.set_ylabel("Humidity [%]")

ax_bathroom.set_title('Movement in the Bathroom')
#ax1.set_title('Bathroom Temperature')
#ax2.set_title('Bathroom Humidity')

ax_bathroom.legend(['Movement'],loc='best')
#ax1.legend(['Temperature'],loc='best')
#ax2.legend(['Humidity'],loc='best')
'''
ax_office.set_ylabel("Movement")
ax_office.set_title('Movement in the Office')
ax_office.legend(['Movement'],loc='best')
'''

ax_hall.set_ylabel("Movement")
ax_hall.set_title('Movement in the Hall')
ax_hall.legend(['Movement'],loc='best')

ax_kitchen.set_ylabel("Movement")
ax_kitchen.set_title('Movement in the Kitchen')
ax_kitchen.legend(['Movement'],loc='best')

ax_bedroom.set_ylabel("Movement")
ax_bedroom.set_title('Movement in the Bedroom')
ax_bedroom.legend(['Movement'],loc='best')

ax_livingroom.set_ylabel("Movement")
ax_livingroom.set_title('Movement in the Living Room')
ax_livingroom.legend(['Movement'],loc='best')


ax_smart.set_ylabel("Energy [A]")
ax_smart.set_title(' Smart Plug consume of the TV ')
ax_smart.legend(['Energy Consume'],loc='best')

'''
my_yticks = ['Open', 'Close', 'Open', 'Open']
ax_door.set_ylabel("Door State")
ax_door.set_title('Outdoor Door State')
ax_door.legend(['Door State'],loc='best')
ax_door.set_yticklabels(my_yticks, rotation=0)


ax_balcony.set_ylabel("Door State")
ax_balcony.set_title('Balcony Door State')
ax_balcony.legend(['Door State'],loc='best')


ax_water_pipe.set_ylabel("Temp. [ºC]")
ax_water_pipe.set_title('Water Pipe Temperature')
ax_water_pipe.legend(['Water Pipe Temperature'],loc='best')


ax_water_meter.set_ylabel("Water Consume [L]")
ax_water_meter.set_title('Water Consume')
ax_water_meter.legend(['Water Consume'],loc='best')
'''
#################################################################################################################################################################################################


#SHOW PLOT
plt.xlabel('Time', fontsize=18)
plt.gca().xaxis.set_major_locator(mdates.HourLocator(interval = 5))
date_format = mpl_dates.DateFormatter('%m-%d %H:%M')

plt.gca().xaxis.set_major_formatter(date_format)
plt.gcf().autofmt_xdate()
plt.show()


