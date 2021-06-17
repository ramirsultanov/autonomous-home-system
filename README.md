# autonomous-home-system

## Description
The project can be described as smart devices control autonomous system app.
It is a project on qt creator, mysql and spring boot using rest api.
Imagine a house with many smart devices which are hard to manage because they need to be manually configured. So, there goes the autonomous home system app which allows you to unite all devices to one app and make it easy to control. And now about the little dramatic part: to achieve the app and devices compatibility, every device should be programmed by one standard which is used by the app. The standard is that a device should send http requests to the server and get a response about config change or actions to do next. But the full-duplex protocol is under development now and, probably, it will be released soon. The server uses a database to share information between users and devices. The users can change the config of devices via the autonomous home system app (see the main features chapter for more detailed description). 

## Prerequisites:
- docker (https://docs.docker.com/engine/install/)
- docker-compose (https://docs.docker.com/compose/install/)

## Installation:
- download docker images, docker-compose configuration, install and run scripts: **download folder https://kpfuru-my.sharepoint.com/:f:/g/personal/ramirrsultanov_stud_kpfu_ru/EtEUPjLhBPxFjELZKahJlksBX4_SgD0R_I5heLxGB-G5RA?e=A9OkgG**
- extract the downloaded archive and go to the directory where files have been extracted
- install docker images to your computer: **sudo chmod +x \*.sh && sudo ./install.sh**

## Launching:
- run docker containers: **sudo ./start.sh**
- run qt app

## Main features:
- user authentication and authorization (admin and user have different access levels)
  - admin: admin:12345
  - user: user:user
- viewing smart devices' name, status, information, and configuration
  - name is shown in the first column
  - status is shown in the second column
  - information is shown in the third column
  - configuration is accessible via the double click on device's name
- changing smart devices' status, configuration
  - status can be changed via the double click on the status followed by the click on the save button in the right part of the main window
  - configuration can be changed via the double click on device's name followed by the click on the save button in the bottom of the configuration window
- quick changing status of all devices to active or inactive
- adding/removing smart devices
  - adding via the button on the top of the main window
  - removing via the configuration menu of the device
- registering new users
- automatic and manual updating of information from a server (the update button on the top of the main window)

## Demonstration:
![unlogged](https://user-images.githubusercontent.com/70936349/122413499-1684b180-cf8f-11eb-875b-2ddd8a40a589.png) Unlogged user main window

![logged_as_user](https://user-images.githubusercontent.com/70936349/122098407-78230f80-ce19-11eb-8d14-2f05bec32323.png) Logged-in user main window

![logged_as_admin](https://user-images.githubusercontent.com/70936349/122098416-7a856980-ce19-11eb-9a8e-4bb7d9ed6c7b.png) Logged-in admin main window

Demo video: https://user-images.githubusercontent.com/70936349/122099492-b79e2b80-ce1a-11eb-8cf2-b03bdb4b7af1.mp4

## Known issues:
- there is no full duplex exchange between a server and devices
- "enable all" and "shutdown all" buttons are changing status of disabled devices
- there is no informative error description when receiving error responses from a server
