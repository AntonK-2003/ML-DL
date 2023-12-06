#importing the required pyspark library 
from pyspark.sql import SparkSession 
from pyspark.ml.evaluation import RegressionEvaluator 
from pyspark.ml.recommendation import ALS 
  
#Setup Spark Session 
spark = SparkSession.builder.appName('Recommender').getOrCreate() 

#CSV file can be downloaded from the link mentioned above. 
data = spark.read.csv('book_ratings.csv', 
                      inferSchema=True,header=True) 
  
data.show(5)

data.describe().show()

# Dividing the data using random split into train_data and test_data  
# in 80% and 20% respectively 
train_data, test_data = data.randomSplit([0.8, 0.2])
# Build the recommendation model using ALS on the training data 
als = ALS(maxIter=5, 
          regParam=0.01, 
          userCol="user_id", 
          itemCol="book_id", 
          ratingCol="rating") 
  
#Fitting the model on the train_data 
model = als.fit(train_data)
# Evaluate the model by computing the RMSE on the test data 
predictions = model.transform(test_data) 
  
#Displaying predictions calculated by the model 
predictions.show()
#Printing and calculating RMSE 
evaluator = RegressionEvaluator(metricName="rmse", labelCol="rating",predictionCol="prediction") 
rmse = evaluator.evaluate(predictions) 
print("Root-mean-square error = " + str(rmse))
#Filtering user with user id "5461" with book id on which it has given the reviews 
user1 = test_data.filter(test_data['user_id']==5461).select(['book_id','user_id']) 
  
#Displaying user1 data 
user1.show()
#Traning and evaluating for user1 with our model trained with the help of training data  
recommendations = model.transform(user1) 
  
#Displaying the predictions of books for user1 
recommendations.orderBy('prediction',ascending=False).show()
spark.stop()
