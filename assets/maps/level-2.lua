mobsCreated = getMobsCreated(MAP)
startTime = getStartTime(MAP)
mobsKilled = getMobsKilled(MAP)

function tablelength(T)
    local count = 0
    for _ in pairs(T) do count = count + 1 end
    return count
end

math.randomseed(os.time())

spawn = {}

table.insert(spawn, {["time"]=4, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})

table.insert(spawn, {["time"]=6, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=6, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=6, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=6, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=7, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=7, ["name"]="chaser", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=7, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=7, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})

table.insert(spawn, {["time"]=10, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=10, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=10, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=10, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})

table.sort( spawn, function (a, b) return a["time"] < b["time"] end)

if mobsKilled >= tablelength(spawn) then
    loadNextLevel(MAP)
end

local i = 0

for k, v in pairs(spawn) do
    if v["time"] <= startTime and i >= mobsCreated then
        createMob(MAP, v["name"], v["x"], v["y"])
    end
    i = i + 1
end