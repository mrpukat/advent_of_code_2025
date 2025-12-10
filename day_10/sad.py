from ortools.linear_solver import pywraplp

# Gave upon  my cpp solution. Not to add more delay on this nigth (i want to sleep this day at least)
# Follows this closely: https://github.com/yolocheezwhiz/adventofcode/blob/main/2025/day10.py
def solve(buttons, wolt):
    # Create the mip solver with the CP-SAT backend.
    solver = pywraplp.Solver.CreateSolver("SAT")

    var = []
    for i in range(len(buttons)):
        var += [solver.IntVar(0.0, solver.infinity(), "v{i}")]

    #print("Number of variables =", solver.NumVariables())

    for i in range(len(wolt)):
        buttonList = []
        for j in range(len(buttons)):
            if (i in buttons[j]):
                buttonList += [var[j]]

        solver.Add(sum(buttonList) == wolt[i])

    #print("Number of constraints =", solver.NumConstraints())

    solver.Minimize(sum(var))
    solver.Solve()

    #print("Objective value =", solver.Objective().Value())

    return solver.Objective().Value()

with open("data.txt", "r") as f:
    res = 0
    for line in f:
        buttons = line[line.index(']') + 2 :line.index('{') - 1].replace('(','').replace(')','').split(' ')
        buttons = [list(map(int, item.split(','))) for item in buttons]

        wolt = [int(i) for i in line[line.index('{') + 1 :-2].split(',')] 

        res = solve(buttons, wolt) + res

    print(res)

