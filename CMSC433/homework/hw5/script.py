things = ["bigburger", "fishjoe", "chessypiza"]
print things

things = [thing.capitalize() if things.index(thing) % 2 == 0 else thing for thing in things]
print things

things = [thing.upper() if things.index(thing) == 1 else thing for thing in things]
print things

food = {"red-meat": {"beef": {}, "lamb": ["baked", "bar-b-qued", "fried"],
"bison": {}}, "poultry": {}, "other": {}}

print food.keys()
print food["red-meat"].keys()
print food["red-meat"]["lamb"]
