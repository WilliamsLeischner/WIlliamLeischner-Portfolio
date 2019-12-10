#!/usr/bin/python
import json
from bson import json_util
from bson.json_util import dumps
import bottle
from bottle import route, run, request, abort
#imports for database
from pymongo import MongoClient
connection = MongoClient('localhost', 27017)
db = connection['market']
collection = db['stocks']

# set up URI paths for REST service
@route('/createStock/<ticker>', method='POST')
def createStock(ticker):
  data = request.json
  data.update( {'Ticker' : ticker} ) #add Ticker key and its value to the passed dictionary.
  print(data)
  for field in data:
    print(data[field])
  document = collection.insert(data)                      #insert data into the collection
  inserted_document = collection.find_one({"_id":document})
  return "Created Document \n "+dumps(inserted_document)+"\n\n " #return inserted document.


@route('/updateStock/<ticker>', method='PUT')
def updateStock(ticker):
  data = request.json         #obtain the request data
  print(data) 
  query = { "Ticker" :ticker} #generate query using for loop to get update values
  for field in data:
    print(data[field])
    updateValues =  { "$set":{field:data[field]}} #Set value of key to key in collection
    collection.update_one(query,updateValues)
  updated_document = collection.find({"Ticker":ticker}) #find all the updated documents returns a curser documenst object
  result= dumps(updated_document)

  return "\nUpdated Values\n"+str(result)+"\n"
  



@route('/getStock/<Ticker>', method='GET')
def getStock(Ticker):
  result = collection.find({"Ticker":Ticker}) #finds all documents whose ticker value is equal to the one passed
  return dumps(result)


@route('/deleteStock/<Ticker>', method='GET')
def deleteStock(Ticker):
  query = {"Ticker" :Ticker} #generate query
  print(query)
  result = collection.delete_many(query) #delete all the documents whose Ticker value is equal to the Ticker value passed
  return "Document with Ticker "+Ticker+" Has been deleted from the stocks Collection"

@route('/stockReport', method='POST')
def create_stockReport(): 
  myList = request.json.get('list')              #retrieves the value of the list key in the url data
  myList = myList.replace("[","")                #removes [
  myList = myList.replace("]","")                #removes ]
  myList = list(myList.split(","))               #create a list from the remaining list
  items = list()
  print(myList)
  #get fields and append to report
  fields = []
  for ticker in myList:
    print(ticker)
    field = getReport(ticker)
    print(field)
    fields.append("Report For Ticker "+ticker+" \n"+field+"\n\n")
  return fields #return a list of fields

#some industry names contain spaces and passing them causes errors. SO I add ; to the spaces then remove them to get orginal name

@route('/industryReport/<industry>', method='GET')
def create_industryReport(industry):
  industry = industry.replace("_"," ")#removes underscore form the string
  print(industry)
  #specifies values to be included in the next line of the pipeline
  included_Values = { '$project': {'Industry':1, 'Ticker':1,'Performance (YTD)':1,'Performance (Week)':1,'Volume':1 } }
  #specifies the types of documents
  document_Type = { '$match': { "Industry": industry } }
  #group sumery data using operators
  grouped_Summery_Data = { '$group': { '_id': "$Industry", 'Average Performance (YTD)':{'$avg':"$Performance (YTD)"},
                           'Average Performance (Week)':{'$avg':'$Performance (Week)'},
                           'Total Volume':{'$sum':'$Volume'} } }
  #detrmine number of items to deal with
  items_Limit = { '$limit' : 5 }
  query = [included_Values,document_Type,grouped_Summery_Data,items_Limit]
                                        #perform the agregation
  result=collection.aggregate(query)
  result = dumps(result)               # convert json dictionary format
  return "\n Portfolio Report For The First Five "+industry+" Industries \n\n "+result+" \n"


@route('/portfolio/<company>', method='GET')
def create_portfolio(company):
  company = company.replace("_"," ") #removes underscore form the string
  print(company)
  query = {"Company":company} #generate query
  result=collection.find(query) #find documents using the query
  result = dumps(result)
  return "\n Portfolio Report For "+company+" Company \n\n "+result+" \n"
    
    

def getReport(ticker):
  #specifies the fields to be passed to the next pipeline
  included_Values = { '$project': { 'Ticker':1,'Performance (YTD)':1,'Performance (Week)':1,'Shares Outstanding':1,'Volume':1 } }
  #specifies the documenst to deal with
  document_Type = { '$match': { "Ticker": ticker } }
  # group and find sum, avg and other operations
  grouped_Summery_Data= { '$group': { '_id': "$Ticker",'Average Performance (YTD)':{'$avg':"$Performance (YTD)"},
                           'Average Performance (Week)':{'$avg':'$Performance (Week)'},
          
                           'Total Volume':{'$sum':'$Volume'} } }
  query = [included_Values,document_Type, grouped_Summery_Data] #generate query
  result=collection.aggregate(query) #performs aggregation
  result = dumps(result)
  return result
  
if __name__ == '__main__':
  run(debug=True,reloader = True)
  #run(host='localhost', port=8080)