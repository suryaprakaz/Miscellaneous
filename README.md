from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import os
import time
from PIL import Image
from PIL import ImageGrab

from email.mime.text import MIMEText
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from smtplib import SMTP
import smtplib
import sys


#directories
SaveDirectory="D:\python_scrape"
chromedriver = "C:\Python27\Scripts\chromedriver"

#Open Site
os.environ["webdriver.chrome.driver"] = chromedriver
driver = webdriver.Chrome(chromedriver)
driver.get("http://172.16.8.22")
time.sleep(2)

#Take Screenshot
img=ImageGrab.grab()
saveas=os.path.join(SaveDirectory,"ScreenShot_.jpg")
img.save(saveas)

driver.quit()
#Email part

recipients = ['suryaprakaz@hotmail.com','sherinejeyaraj@gmail.com']
emaillist = [elem.strip().split(',') for elem in recipients]

msg = MIMEMultipart()
msg['Subject'] = "Company Update"
msg['From'] = "suryaprakaz@hotmail.com"
msg['Reply-to'] = "suryaprakaz@hotmail.com"

print " Sending Email..."

part = MIMEText("Hi, please find the attached file")
msg.attach(part)
 
part = MIMEApplication(open("ScreenShot_.jpg","rb").read())
part.add_header('Content-Disposition', 'attachment', filename="ScreenShot_.jpg")
msg.attach(part)
print "Attaching file..."

server = smtplib.SMTP("smtp.live.com",25)
server.ehlo()
server.starttls()
server.login("suryaprakaz@hotmail.com", "unbefuckinglievable9090")
 
server.sendmail(msg['From'], emaillist , msg.as_string())
print " Email sent"


