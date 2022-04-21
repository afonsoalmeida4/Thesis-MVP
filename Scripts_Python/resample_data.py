import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator


col_names_pir = ["ts", "data_presenceSensor_3","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_door = ["ts", "data_analogInput_4","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_smart = ["ts", "data_analogInput_3","data_temperatureSensor_0","data_humiditySensor_1"]


pir_hall_df= pd.read_csv('pir_45774d90-8358-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
data_df = pir_hall_df.resample('5min').ffill() 
data_df.to_csv('pir_45774d90-8358-11ec-b720-2bc6d4a3e96edata.csv')
print(data_df)

#pir_bathroom_df.to_csv('resample_pir')
#pir_bathroom_df.open.resample('SMS').bfill()




'''
pir_office_df= pd.read_csv('pir_5438cf60-8359-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_hall_df= pd.read_csv('pir_45774d90-8358-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_kitchen_df= pd.read_csv('pir_d334f6b0-6a34-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_bedroom_df= pd.read_csv('pir_de9978c0-6a5f-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_livingroom_df= pd.read_csv('pir_e2a8b950-3191-11ec-a5c0-8f487cf8beb8data.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
door_df= pd.read_csv('door_sensor_3f0e4050-4e0e-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_door, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
balcony_df= pd.read_csv('door_sensor_fd142060-835b-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_door, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
smart_plug_df= pd.read_csv('smart_plug_data.csv', sep=',',usecols=col_names_smart, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')




#fig, (ax, ax1,ax2) = plt.subplots(3,1,figsize=(15, 10),sharex=True, sharey=True)
fig, (ax_bathroom, ax_office,ax_hall,ax_kitchen,ax_bedroom,ax_livingroom,ax_door,ax_balcony,ax_smart) = plt.subplots(9,1,figsize=(20, 100))
ax_bathroom.plot(pir_bathroom_df["data_presenceSensor_3"])
ax_office.plot(pir_office_df["data_presenceSensor_3"])
ax_hall.plot(pir_hall_df["data_presenceSensor_3"])
ax_kitchen.plot(pir_kitchen_df["data_presenceSensor_3"])
ax_bedroom.plot(pir_bedroom_df["data_presenceSensor_3"])
ax_livingroom.plot(pir_livingroom_df["data_presenceSensor_3"])
ax_door.plot(door_df["data_analogInput_4"])
ax_balcony.plot(balcony_df["data_analogInput_4"])
ax_smart.plot(smart_plug_df["data_analogInput_3"])

#ax1.plot(fixed_df["data_temperatureSensor_0"],color="orange")
#ax2.plot(fixed_df["data_humiditySensor_1"],color="purple")

ax_bathroom.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_office.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_hall.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_kitchen.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_bedroom.yaxis.set_major_locator(MaxNLocator(integer=True))
ax_livingroom.yaxis.set_major_locator(MaxNLocator(integer=True))


ax_bathroom.set_ylabel("Movement")
ax_bathroom.set_title('Movement in the Bathroom')
ax_bathroom.legend(['Movement'],loc='best')

ax_office.set_ylabel("Movement")
ax_office.set_title('Movement in the Office')
ax_office.legend(['Movement'],loc='best')

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

ax_door.set_ylabel("Door State")
ax_door.set_title('Outdoor Door State')
ax_door.legend(['Door State'],loc='best')

ax_balcony.set_ylabel("Door State")
ax_balcony.set_title('Balcony Door State')
ax_balcony.legend(['Door State'],loc='best')

ax_smart.set_ylabel("Energy Consume [A]")
ax_smart.set_title(' Smart Plug consume of the TV ')
ax_smart.legend(['Energy Consume'],loc='best')



plt.xlabel('Time', fontsize=18)
plt.show()

'''