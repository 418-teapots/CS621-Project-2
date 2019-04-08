import os
import sys
import pandas as pd
import seaborn as sns

print ('Running for SPQ')
os.system('cd ns-3.29' + ' && ' + './waf --run "cs621-dev02 --conf=SPQ"')
print ('Running for DRR')
os.system('cd ns-3.29' + ' && ' + './waf --run "cs621-dev02 --conf=DRR"')

stats_SPQ = "./ns-3.29/stats_SPQ.csv"
stats_DRR = "./ns-3.29/stats_DRR.csv"
if not (os.path.isfile(stats_SPQ) and os.path.isfile(stats_DRR)):
    sys.exit()

df1 = pd.read_csv(stats_SPQ)
df2 = pd.read_csv(stats_DRR)
df1['packets'] = df.groupby('flowID')['numPackets'].diff()
df1['duration'] = df.groupby('flowID')['timePacketReceived'].diff()
df1['rate'] = df1['packets']/df1['duration']
df2['packets'] = df.groupby('flowID')['numPackets'].diff()
df2['duration'] = df.groupby('flowID')['timePacketReceived'].diff()
df2['rate'] = df2['packets']/df2['duration']

sns_plot1 = sns.set(style='darkgrid')
sns_plot1 = sns.lineplot(x='timePacketReceived', y='rate', data=df1)
sns_plot1.get_figure().savefig("SPQ.png")
sns_plot2 = sns.set(style='darkgrid')
sns_plot2 = sns.lineplot(x='timePacketReceived', y='rate', data=df2)
sns_plot2.get_figure().savefig("DRR.png")
