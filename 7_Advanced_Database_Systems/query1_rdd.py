import csv
from io import StringIO
from pyspark.sql import SparkSession

def split_complex(x):
	return list(csv.reader(StringIO(x), delimiter=','))[0]

spark = SparkSession.builder.appName('query1_rdd').getOrCreate()

sc = spark.sparkContext

res = sc.textFile('hdfs://master:9000/movies/movies.csv') \
	.map(lambda x : split_complex(x)) \
	.filter(lambda x : x if x[3] != "" and x[5] != '0' and x[6] != '0' and int(x[3].split('-')[0]) >= 2000 else None) \
	.map(lambda x : (x[3].split('-')[0], x)) \
	.reduceByKey(lambda x1, x2 : max(x1, x2, key=lambda x : ((float(x[6])-float(x[5]))/float(x[5]))*100)) \
	.map(lambda x : (x[0], x[1][1], round(((float(x[1][6])-float(x[1][5]))/float(x[1][5])), 2))) \
	.collect()

for f in res:
	print(f)
