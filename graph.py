import os
import sys
import pandas as pd
import seaborn as sns

stats_SPQ = "./ns-3.29/stats_SPQ.csv"
stats_DRR = "./ns-3.29/stats_DRR.csv"
if not (os.path.isfile(stats_SPQ) and os.path.isfile(stats_DRR)):
    sys.exit()

df1 = pd.read_csv(stats_SPQ)
df2 = pd.read_csv(stats_DRR)
df1['timePacketReceived'] = df1['timePacketReceived'].round(1)
df2['timePacketReceived'] = df2['timePacketReceived'].round(1)
df1['packets'] = df1.groupby('flowID')['numPackets'].diff()
df1['duration'] = df1.groupby('flowID')['timePacketReceived'].diff()
df1['rate'] = df1['packets']/df1['duration']
df2['packets'] = df2.groupby('flowID')['numPackets'].diff()
df2['duration'] = df2.groupby('flowID')['timePacketReceived'].diff()
df2['rate'] = df2['packets']/df2['duration']
df1['rate'] = df1['rate'].fillna(0)
df2['rate'] = df2['rate'].fillna(0)
df1['duration'] = df1['duration'].fillna(0)
df2['duration'] = df2['duration'].fillna(0)
df1['packets'] = df1['packets'].fillna(0)
df2['packets'] = df2['packets'].fillna(0)
df1.to_csv('SPQ.csv', index=False)
df2.to_csv('DRR.csv', index=False)

print (df1.head())
print (df2.head())

sns_plot1 = sns.set(style='darkgrid')
sns_plot1 = sns.lineplot(x='timePacketReceived', y='rate', data=df1)
sns_plot1.figure.tight_layout()
sns_plot1.get_figure().savefig("SPQ.png", dpi=400)
sns_plot2 = sns.set(style='darkgrid')
sns_plot2 = sns.lineplot(x='timePacketReceived', y='rate', data=df2)
sns_plot2.figure.tight_layout()
sns_plot2.get_figure().savefig("DRR.png", dpi=400)
