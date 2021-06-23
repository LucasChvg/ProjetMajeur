import smbus
import time
from datetime import datetime
import MySQLdb

bus=smbus.SMBus(1)
address= 0x12 #adress of the slave

valeurMaxTemp = 50
valeurMaxGaz = 60

delai = 60 #Temps en seconde
nextTime=0

DB_HOST = '127.0.0.1'
DB_USER = 'root'
DB_PASSWORD = 'xsmart'
DB_SCHEMA = 'xsmartfirekiller'


#connection to the database
db = MySQLdb.connect(host=DB_HOST, user=DB_USER, passwd=DB_PASSWORD, db=DB_SCHEMA)

dbc=db.cursor()

dbc.execute("SELECT * FROM data_sensor")

databdd_gaz = dbc.fetchall()

print('connection vers bdd reussi')

reponse = [0,0]

while(True):
    if(time.time() > nextTime):
        nextTime = time.time()+delai

        now = datetime.now()
        print("date = ", now)

        for i in range(2):
            reponse[i] = bus.read_byte(address)
        
        print("reponse :")
        print(reponse)
        
        
        VAL_TEMP = reponse[0]
        VAL_GAZ = reponse[1]

        #check if values are too high
        #And insert data into the database
        if(VAL_GAZ > valeurMaxGaz or VAL_TEMP > valeurMaxTemp):
            #dbc.execute("INSERT INTO data_sensor(date,temperature,gaz, incident) VALUES (%s,%s,%s,%s);", (now, VAL_TEMP, VAL_GAZ, 1))
            dbc.execute("INSERT INTO data_sensor(date,temperature,gaz) VALUES (%s,%s,%s);", (now, VAL_TEMP, VAL_GAZ))
            dbc.execute("INSERT INTO data_incident(date,i_temperature,i_gaz) VALUES (%s,%s,%s);", (now, VAL_TEMP, VAL_GAZ)) 
            #dbc.execute("UPDATE data SET id_plant_capteur='%s', data_eau='%s', data_temperature='%s', data_humidite='%s', data_expo='%s' WHERE id_plant_capteur = '%s'; ", (plant1,VAL_NIV_EAU,VAL_T,VAL_HTERRE_1,VAL_LUM,plant1))
            db.commit()
            print ("Database updated")
            
        else:
            if(VAL_GAZ != ""):
                #dbc.execute("INSERT INTO data_sensor(date,temperature,gaz, incident) VALUES (%s,%s,%s,%s);", (now, VAL_TEMP, VAL_GAZ, 0))
                dbc.execute("INSERT INTO data_sensor(date,temperature,gaz) VALUES (%s,%s,%s);", (now, VAL_TEMP, VAL_GAZ))
                #dbc.execute("UPDATE data SET id_plant_capteur='%s', data_eau='%s', data_temperature='%s', data_humidite='%s', data_expo='%s' WHERE id_plant_capteur = '%s'; ", (plant1,VAL_NIV_EAU,VAL_T,VAL_HTERRE_1,VAL_LUM,plant1))
                db.commit()
                print ("Database updated")
            else:
                print("no values detected !")
        

db.close()
