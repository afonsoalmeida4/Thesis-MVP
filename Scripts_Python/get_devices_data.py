import sys
import requests
import json
import pandas as pd
from datetime import datetime, timedelta

smart_plug_id = "7cec0870-4d3d-11ec-b720-2bc6d4a3e96e"
door_board_id = "3f0e4050-4e0e-11ec-b720-2bc6d4a3e96e"
balcony_door_id = "fd142060-835b-11ec-b720-2bc6d4a3e96e"
pir_office_id = "5438cf60-8359-11ec-b720-2bc6d4a3e96e"
pir_hall_id = "45774d90-8358-11ec-b720-2bc6d4a3e96e"
pir_bedroom_id = "de9978c0-6a5f-11ec-b720-2bc6d4a3e96e"
pir_bathroom_id = "7519aca0-6a44-11ec-b720-2bc6d4a3e96e"
pir_kitchen_id = "d334f6b0-6a34-11ec-b720-2bc6d4a3e96e"
pir_livingroom_id = "e2a8b950-3191-11ec-a5c0-8f487cf8beb8"
water_pipe_id = "baf97090-8ced-11ec-b720-2bc6d4a3e96e"
water_meter_id = "86a48d40-4ede-11ec-b720-2bc6d4a3e96e"




def smart_plug_json_csv(data):
    smart_plug_info = pd.DataFrame(data['data_analogInput_3'])
    smart_plug_info = smart_plug_info.rename(columns={'value': 'data_analogInput_3'})
    all = smart_plug_info.join(pd.DataFrame(data['data_temperatureSensor_0']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_temperatureSensor_0'})
    all = all.join(pd.DataFrame(data['data_humiditySensor_1']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_humiditySensor_1'})
    # change unix time to normal date, add 1h because we want UTC+1 timezone, rmv ms
    all['ts'] = pd.to_datetime(all['ts']/1000,unit='s') 
    all['ts']= all['ts'].astype('datetime64[s]')
    return all.iloc[::-1]

def pir_json_csv(data):
    pir_info = pd.DataFrame(data['data_presenceSensor_3'])
    pir_info = pir_info.rename(columns={'value': 'data_presenceSensor_3'})
    #state = state.join(pd.DataFrame(data['id']).set_index('ts'), on='ts')   
    #state = state.rename(columns={'value': 'id'})
    all = pir_info.join(pd.DataFrame(data['data_temperatureSensor_0']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_temperatureSensor_0'})
    all = all.join(pd.DataFrame(data['data_humiditySensor_1']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_humiditySensor_1'})
    # change unix time to normal date, add 1h because we want UTC+1 timezone, rmv ms
    all['ts'] = pd.to_datetime(all['ts']/1000,unit='s') 
    all['ts']= all['ts'].astype('datetime64[s]')
    return all.iloc[::-1]

def door_sensor_json_csv(data):
    door_info = pd.DataFrame(data['data_analogInput_4'])
    door_info = door_info.rename(columns={'value': 'data_analogInput_4'})
    #state = state.join(pd.DataFrame(data['id']).set_index('ts'), on='ts')   
    #state = state.rename(columns={'value': 'id'})
    all = door_info.join(pd.DataFrame(data['data_temperatureSensor_0']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_temperatureSensor_0'})
    all = all.join(pd.DataFrame(data['data_humiditySensor_1']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_humiditySensor_1'})
    # change unix time to normal date, add 1h because we want UTC+1 timezone, rmv ms
    all['ts'] = pd.to_datetime(all['ts']/1000,unit='s') 
    all['ts']= all['ts'].astype('datetime64[s]')
    return all.iloc[::-1]


def water_pipe_json_csv(data):
    smart_plug_info = pd.DataFrame(data['data_temperatureSensor_0'])
    smart_plug_info = smart_plug_info.rename(columns={'value': 'data_temperatureSensor_0'})
    all = smart_plug_info.join(pd.DataFrame(data['data_humiditySensor_1']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_humiditySensor_1'})
    # change unix time to normal date, add 1h because we want UTC+1 timezone, rmv ms
    all['ts'] = pd.to_datetime(all['ts']/1000,unit='s') 
    all['ts']= all['ts'].astype('datetime64[s]')
    return all.iloc[::-1]



def water_meter_json_csv(data):
    door_info = pd.DataFrame(data['data_analogInput_4'])
    door_info = door_info.rename(columns={'value': 'data_analogInput_4'})
    #state = state.join(pd.DataFrame(data['id']).set_index('ts'), on='ts')   
    #state = state.rename(columns={'value': 'id'})
    all = door_info.join(pd.DataFrame(data['data_temperatureSensor_0']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_temperatureSensor_0'})
    all = all.join(pd.DataFrame(data['data_humiditySensor_1']).set_index('ts'), on='ts')   
    all = all.rename(columns={'value': 'data_humiditySensor_1'})
    # change unix time to normal date, add 1h because we want UTC+1 timezone, rmv ms
    all['ts'] = pd.to_datetime(all['ts']/1000,unit='s') 
    all['ts']= all['ts'].astype('datetime64[s]')
    return all.iloc[::-1]

#def vib_noise_json_csv(data, type):
#    all = pd.DataFrame(data[type])
#    # change unix time to normal date, add 1h because we want UTC+1 timezone, rmv ms
#    all['ts'] = pd.to_datetime(all['ts']/1000,unit='s') + timedelta(hours=1)
#    all['ts']= all['ts'].astype('datetime64[s]')
#    return all.iloc[::-1]

def getToken():
    username = 'afonso.claudio.almeida@tecnico.ulisboa.pt' #email used to create your ThingsBoard account (your email associated with tennant)
    password = 'AfonsoAlmeida1702'		#password of your ThingsBoard account (or your tennant account)
    url = 'http://iot.istartlab.tecnico.ulisboa.pt/api/auth/login'
    #url = 'https://thingsboard.cloud/api/auth/login'
    headers = {'Content-Type': 'application/json', 'Accept': 'application/json'}
    loginJSON = {'username': username, 'password': password}
    tokenAuthResp = requests.post(url, headers=headers, json=loginJSON).json()
    #print(tokenAuthResp)
    token = tokenAuthResp['token']
    return token

tkn = getToken()

my_headers = {'X-Authorization':  "Bearer " + tkn, "Content-Type" : "application/json"}
#print(my_headers)
#o f6 etc etc é o uuid do device que queres os dados
#url = "https://thingsboard.cloud/api/plugins/telemetry/DEVICE/f60b8040-d4da-11eb-ae0e-1f8899a6f9b3/keys/timeseries"

#response = requests.get(url, headers=my_headers)
#print(response) , print(response.text)

my_headers = {'X-Authorization':  "Bearer " + tkn, "Content-Type" : "application/json"}
#print(my_headers)

# start & end unix timestamp (ms)
startTS = "1645056000000"   #17 Feb 2022 00:00:00 GMT+01:00
endTS = "1647475200000"     #16 March 2022 00:00:00 GMT+01:00
#max number of datapoints to extract
limit = "1000000000"

date_filename = "data.csv"

# Get lastest timeseries value
#url = "https://thingsboard.cloud/api/plugins/telemetry/DEVICE/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/values/timeseries?keys=temperature,distance,relative_hum,analog_in,rgb_info"
# Get historical timeseries data
# Get data from Smart Plug (get device id from ThingsBoard devices page on your account)
device_id = smart_plug_id
keys = "data_analogInput_3,data_temperatureSensor_0,data_humiditySensor_1"      #info to extract
url = "http://iot.istartlab.tecnico.ulisboa.pt/api/plugins/telemetry/DEVICE/" + device_id + "/values/timeseries?keys=" + keys + "&startTs=" + startTS + "&endTs=" + endTS + "&interval=0&limit=" + limit + "&agg=NONE"
response = requests.get(url, headers=my_headers)
#print(response.text) , print(response.status_code) , print(response.json())
j = json.loads(response.text)
to_file = smart_plug_json_csv(j)
to_file.to_csv("smart_plug_" + date_filename, index=False)
print("SMART_PLUG DONE")


# Get data from all door devices 
# array with all door devices id (get device id from ThingsBoard devices page on your account)

devices = [door_board_id,balcony_door_id]
keys = "data_analogInput_4,data_temperatureSensor_0,data_humiditySensor_1"      #info to extract
cnt = 1
for dev in devices:
    url = "http://iot.istartlab.tecnico.ulisboa.pt/api/plugins/telemetry/DEVICE/" + dev + "/values/timeseries?keys=" + keys + "&startTs=" + startTS + "&endTs=" + endTS + "&interval=0&limit=" + limit + "&agg=NONE"

    response = requests.get(url, headers=my_headers)
    j = json.loads(response.text)

    to_file = door_sensor_json_csv(j)
    to_file.to_csv("door_sensor_" + dev + date_filename, index=False)
    #cnt = cnt + 1
print("DOOR SENSOR DONE")

# Get data from all pir devices 
# array with all pir nodes device id (get device id from ThingsBoard devices page on your account)
# 
devices = [pir_bathroom_id, pir_office_id, pir_hall_id, pir_bedroom_id, pir_kitchen_id,pir_livingroom_id]
keys = "data_presenceSensor_3,data_temperatureSensor_0,data_humiditySensor_1"     #info to extract
cnt = 0
for dev in devices:
    url = "http://iot.istartlab.tecnico.ulisboa.pt/api/plugins/telemetry/DEVICE/" + dev + "/values/timeseries?keys=" + keys + "&startTs=" + startTS + "&endTs=" + endTS + "&interval=0&limit=" + limit + "&agg=NONE"

    response = requests.get(url, headers=my_headers)
    j = json.loads(response.text)

    to_file = pir_json_csv(j)
    to_file.to_csv("pir_" + dev + date_filename, index=False)
    #cnt = cnt + 1
print("PIR DONE")



# Get data from water pipe devices 
# array with water pipe device id (get device id from ThingsBoard devices page on your account)
device_id = water_pipe_id
keys = "data_temperatureSensor_0,data_humiditySensor_1"      #info to extract
url = "http://iot.istartlab.tecnico.ulisboa.pt/api/plugins/telemetry/DEVICE/" + device_id + "/values/timeseries?keys=" + keys + "&startTs=" + startTS + "&endTs=" + endTS + "&interval=0&limit=" + limit + "&agg=NONE"
response = requests.get(url, headers=my_headers)
#print(response.text) , print(response.status_code) , print(response.json())
j = json.loads(response.text)
to_file = water_pipe_json_csv(j)
to_file.to_csv("water_pipe_" + date_filename, index=False)
print("WATER PIPE DONE")


# Get data from water meter devices 
# array with water meter device id (get device id from ThingsBoard devices page on your account)
device_id = water_meter_id
keys = "data_analogInput_4,data_temperatureSensor_0,data_humiditySensor_1"      #info to extract
url = "http://iot.istartlab.tecnico.ulisboa.pt/api/plugins/telemetry/DEVICE/" + device_id + "/values/timeseries?keys=" + keys + "&startTs=" + startTS + "&endTs=" + endTS + "&interval=0&limit=" + limit + "&agg=NONE"
response = requests.get(url, headers=my_headers)
#print(response.text) , print(response.status_code) , print(response.json())
j = json.loads(response.text)
to_file = water_meter_json_csv(j)
to_file.to_csv("water_meter_" + date_filename, index=False)
print("WATER METER DONE")

'''

# Get all data from all VIB-NOISE devices 
# array with all Vibration & Noise nodes device id (get device id from ThingsBoard devices page on your account)
devices = ["xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"]
cnt = 1
for dev in devices:
    # Extract Vibration Values
    keys = "value"
    url = "https://thingsboard.cloud/api/plugins/telemetry/DEVICE/" + dev + "/values/timeseries?keys=" + keys + "&startTs=" + startTS + "&endTs=" + endTS + "&interval=0&limit=" + limit + "&agg=NONE"
    response = requests.get(url, headers=my_headers)
    j = json.loads(response.text)
    to_file = vib_noise_json_csv(j,'value')
    to_file.to_csv("vib" + str(cnt) + date_filename, index=False)

    # Extract Noise Values
    keys = "mic"
    url = "https://thingsboard.cloud/api/plugins/telemetry/DEVICE/" + dev + "/values/timeseries?keys=" + keys + "&startTs=" + startTS + "&endTs=" + endTS + "&interval=0&limit=" + limit + "&agg=NONE"
    response = requests.get(url, headers=my_headers)
    j = json.loads(response.text)
    to_file = vib_noise_json_csv(j,'mic')
    to_file.to_csv("noise" + str(cnt) + date_filename, index=False)
    cnt = cnt + 1
print("VIB-NOISE DONE")
'''