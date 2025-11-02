import pandas as pd

PLAYED_GAMES = 3

data_file = pd.read_csv('wwc.csv')
score_board = pd.DataFrame()

teams = set(list(data_file['Team1']) + list(data_file['Team2']))
score_board['Teams'] = list(teams)

points, goals, played, wins, losts, draws = [], [], [], [], [], []
for team in score_board['Teams']:
    pt_team, goal_diff, team_count_win, team_count_draw = 0, 0, 0, 0
    games_team = data_file[(data_file['Team1'] == team) | (data_file['Team2'] == team)]
    print("TEAM:", team)
    for _, row in games_team.iterrows():
        if row['Team1'] == team:
            if row['Score1'] > row['Score2']:
                pt_team += 3
                team_count_win +=1
            if row['Score2'] == row['Score1']:
                pt_team += 1
                team_count_draw += 1
            goal_diff += row['Score1'] - row['Score2']
        elif row['Team2'] == team:
            if row['Score2'] > row['Score1']:
                pt_team += 3
                team_count_win += 1
            if row['Score2'] == row['Score1']:
                pt_team += 1
                team_count_draw += 1
            goal_diff += row['Score2'] - row['Score1']
    team_count_lost = PLAYED_GAMES - (team_count_win + team_count_draw)
    played.append(PLAYED_GAMES)
    draws.append(team_count_draw)
    losts.append(team_count_lost)
    points.append(pt_team)
    goals.append(goal_diff)
    wins.append(team_count_win)

score_board['P'] = played
score_board['W'] = wins
score_board['L'] = losts
score_board['D'] = draws 
score_board['Pt'] = points
score_board['GD'] = goals
score_board = score_board.sort_values(by = ['Pt', 'GD'], ascending=False)
score_board.index = range(1, score_board.shape[0] + 1)
#score_board.to_html('wwcScore.html')


print(data_file)
print("\n###########CLASSIFICA############\n")
print(score_board )
