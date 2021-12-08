import requests
import urllib3
import os
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

auth_url = "https://www.strava.com/oauth/token"
activites_url = "https://www.strava.com/api/v3/athlete/activities"

payload = {
    'client_id': "69326",
    'client_secret': 'ec5fcd70b04bf18f7cf67f0b58f3682441aad1c5',
    'refresh_token': 'ac3827247bf6d631564e1beefb714fa1b850c01a',
    'grant_type': "refresh_token",
    'f': 'json'
}

print("Requesting Token...\n")
res = requests.post(auth_url, data=payload, verify=False)
access_token = res.json()['access_token']
print("Access Token = {}\n".format(access_token))

header = {'Authorization': 'Bearer ' + access_token}
param = {'per_page': 200, 'page': 1}
my_dataset = requests.get(activites_url, headers=header, params=param).json()

# ---------------------------------------------------------------------------------

length = (len(my_dataset))

# finding the last activity already in file to compare with new activities
with open('/Users/timhyde/Desktop/stravaDataFiles/distance.txt') as f:
    for line in f:
        pass
    last_line = line

f.close()

file1 = open("/Users/timhyde/Desktop/stravaDataFiles/name.txt", "a")
file2 = open("/Users/timhyde/Desktop/stravaDataFiles/distance.txt", "a")
file3 = open("/Users/timhyde/Desktop/stravaDataFiles/moving_time.txt", "a")
file4 = open("/Users/timhyde/Desktop/stravaDataFiles/max_heartrate.txt", "a")
file5 = open("/Users/timhyde/Desktop/stravaDataFiles/average_heartrate.txt", "a")

file6 = open("/Users/timhyde/Desktop/stravaDataFiles/total_elevation_gain.txt", "a")
file7 = open("/Users/timhyde/Desktop/stravaDataFiles/start_date_local.txt", "a")


# f2 returns the number of new activities
def f2(last_line):
    for i in range (length - 1, -1, -1):
        if (last_line == (str((my_dataset[i]["distance"] / 1600)) + "\n")):
            return i

marker = f2(last_line)
print(str(marker) + " activites to add...")

# currently this loop only checks that distance isn't the same for new activites.
# there is room for error with this method, should also check total time.
def f1(last_line):
    for i in range (marker - 1, -1, -1):
        if (last_line != (str((my_dataset[i]["distance"] / 1600)) + "\n")):
            file1.write(my_dataset[i]["name"] + "\n")
            file2.write(str((my_dataset[i]["distance"] / 1600)) + "\n")
            file3.write(str((my_dataset[i]["moving_time"]) / 60) + "\n")
            file4.write(str(my_dataset[i]["max_heartrate"]) + "\n")
            file5.write(str(my_dataset[i]["average_heartrate"]) + "\n")
            file6.write(str(my_dataset[i]["total_elevation_gain"]) + "\n")
            file7.write(str(my_dataset[i]["start_date_local"]) + "\n")
            print("writing new activity...")
        else:
            print("returning...")
            return

f1(last_line)

file1.close()
file2.close()
file3.close()
file4.close()
file5.close()
file6.close()
file7.close()

print("done")

#activities.columns