import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import time
import numpy as np

#Variables
count_baths = 0
index = 0
flag = 1
array_time = []
average = 0
index_flag = 0



#Columns Information
col_names_pir = ["ts", "data_presenceSensor_3","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_door = ["ts", "data_analogInput_4","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_smart = ["ts", "data_analogInput_3","data_temperatureSensor_0","data_humiditySensor_1"]
col_names_pipe = ["ts", "data_temperatureSensor_0","data_humiditySensor_1"]




#bathroom data resample
pir_bathroom_df= pd.read_csv('pir_7519aca0-6a44-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_bath_resample_df = pir_bathroom_df.resample('1min').ffill()
pir_bath_resample_df = pd.DataFrame(pir_bath_resample_df, columns= ["data_presenceSensor_3","data_temperatureSensor_0","data_humiditySensor_1"]) 
pir_bath_resample_df.to_csv('pir_7519aca0-6a44-11ec-b720-2bc6d4a3e96edata_resample.csv')


#water data resample
water_pipe_df= pd.read_csv('water_pipe_data.csv', sep=',',usecols=col_names_pipe, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
water_pipe_resample_df = water_pipe_df.resample('1min').ffill()
water_pipe_resample_df = pd.DataFrame(water_pipe_resample_df, columns= ["data_temperatureSensor_0","data_humiditySensor_1"]) 
water_pipe_resample_df.to_csv('water_pipe_data.csv_resample.csv')




#hall data resample
pir_hall_df= pd.read_csv('pir_45774d90-8358-11ec-b720-2bc6d4a3e96edata.csv', sep=',',usecols=col_names_pir, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
pir_hall_resample_df = pir_hall_df.resample('1min').ffill()
pir_hall_resample_df = pd.DataFrame(pir_hall_resample_df, columns= ["data_presenceSensor_3"]) 
pir_hall_resample_df.to_csv('pir_45774d90-8358-11ec-b720-2bc6d4a3e96edata_resample.csv')


#outdoor door data resample
door_df= pd.read_csv('door_sensor_data.csv', sep=',',usecols=col_names_door, encoding='latin1', parse_dates=['ts'], dayfirst=True, index_col='ts')
door_resample_df = door_df.resample('1S').first().ffill()
door_resample_df = pd.DataFrame(door_resample_df, columns= ["data_analogInput_4"]) 
door_resample_df.to_csv('door_sensor_data_resample.csv')





#Put the data with the same index    
while (pir_bath_resample_df.index[index] != water_pipe_resample_df.index[0] and index_flag == 0):
    index = index + 1
else:
    index_flag = 1

    


#Extract the data that we want 
for i in range(index,len(pir_bath_resample_df) - 1):
    index = index + 1
    if pir_bath_resample_df.iloc[index,1] > 0:
        if water_pipe_resample_df.loc[pir_bath_resample_df.index[index],'data_temperatureSensor_0'] > 25:
            if pir_bath_resample_df.iloc[index,2] > 65 and flag == 1:
                count_baths = count_baths + 1
                flag = 0
                start_date = pd.Timestamp( water_pipe_resample_df.index[index])

    if water_pipe_resample_df.loc[pir_bath_resample_df.index[index],'data_temperatureSensor_0'] < 25 and flag ==0:
        #if pir_bath_resample_df.iloc[index,2] < 65 and flag == 0:
        flag = 1
        end_date =  pd.Timestamp(water_pipe_resample_df.index[index])
        difference_time = (time.mktime(start_date.timetuple()) - time.mktime(end_date.timetuple()))
        difference_time_abs = abs(difference_time)
        array_time.append(difference_time_abs)



#Number of baths
print('Number of Baths:')
print (count_baths)


#average bath time
average = np.mean(array_time)
format_time = time.strftime('%H:%M:%S', time.gmtime(abs(average)))
print ('Average Bath Time:')
print(format_time)



###############################################################################################################################
#print(water_pipe_resample_df)
#print(water_pipe_resample_df.iloc[1000,0])
#print(water_pipe_resample_df.index[water_pipe_resample_df['ts']==pir_bath_resample_df.index[1000]])
#print(water_pipe_resample_df.loc['2022-02-16 16:41:00'])
#print('Water Pipe ') , print(water_pipe_resample_df.loc[pir_bath_resample_df.index[1038],'data_temperatureSensor_0'])
#print (water_pipe_resample_df.index[12])