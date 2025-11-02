import pandas as pd

table = pd.DataFrame()
table['ColA'] = [1, 2, 3, 4, 5]  # aggiungere colonne, stesso numero di elementi delle colonne
table['ColB'] = [3, 7, 8, 5, 2]
n_row = table.shape[0]
n_col = table.shape[1]
# print(table.describe())
# print(table['ColB'].min())
# print(table['ColB'].max())
# print(table['ColB'].mean())ce
table['ColC'] = [1, 2, '34a', 5, 6.3]
# dtype restituisce il tipo 
table['ColD'] = 2*table['ColA']
table['ColE'] = table['ColA'] - table['ColB']
# print('\n' + str(table))
# print('\n' + str(table[table['ColA'] > 4]))
#table.columns = ['A', 'B', 'C', 'D', 'E']
col_A_True = table[table['ColA'] > 4]
col_A_True.index = range(col_A_True.shape[0]) #reindicizzare sottotabelle

t = table.iloc[0:2, 1:3] # slice delle righe 0 e 1 e slice delle colonne 1 e 2
c = table.loc[:, 'ColA':'ColC'] # slice delle colonne usando i nomi

######################################################

classifica = pd.DataFrame()
table_wc = pd.read_csv('wwc.csv')
table_wc['Score_diff'] = table_wc['Score1'] - table_wc['Score2']
print(table_wc)
l = list(table_wc['Team1']) + list(table_wc['Team2'])
teams = {}
for t in l:
    if t not in teams:
        teams[t] = None
classifica['Team'] = teams.keys()
scores = []
diff_goals = []
for team in classifica['Team']:
    punti_team = 0
    goals = 0
    games_team = table_wc[(table_wc['Team1'] == team) | (table_wc['Team2'] == team)]
    for _, x in games_team.iterrows(): # games_team.iterrows() = (indexRow, Row)
        if x['Team1'] == team:
            if x['Score1'] > x['Score2']:
                punti_team += 3
        if x['Team2'] == team:
            if x['Score2'] > x['Score1']:
                punti_team += 3
        if x['Score1'] == x['Score2'] :
                punti_team += 1
        diff_goals.append(goals)
    scores.append(punti_team)
classifica['Points'] = scores
classifica = classifica.sort_values(by = 'Points', ascending=False)        
print(classifica)

#print(games_team)
