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

table.insert(spawn, {["time"]=4, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=4, ["name"]="shooter", ["x"]=1600, ["y"]=math.random(100, 780)})

table.insert(spawn, {["time"]=6, ["name"]="chaser", ["x"]=1600, ["y"]=450})
table.insert(spawn, {["time"]=7, ["name"]="dumb", ["x"]=1600, ["y"]=500})
table.insert(spawn, {["time"]=7, ["name"]="dumb", ["x"]=1600, ["y"]=400})
table.insert(spawn, {["time"]=8, ["name"]="dumb", ["x"]=1600, ["y"]=350})
table.insert(spawn, {["time"]=8, ["name"]="dumb", ["x"]=1600, ["y"]=550})
table.insert(spawn, {["time"]=9, ["name"]="dumb", ["x"]=1600, ["y"]=300})
table.insert(spawn, {["time"]=9, ["name"]="dumb", ["x"]=1600, ["y"]=600})
table.insert(spawn, {["time"]=10, ["name"]="dumb", ["x"]=1600, ["y"]=250})
table.insert(spawn, {["time"]=10, ["name"]="dumb", ["x"]=1600, ["y"]=650})

table.insert(spawn, {["time"]=12, ["name"]="shooter", ["x"]=1600, ["y"]=450})
table.insert(spawn, {["time"]=12, ["name"]="shooter", ["x"]=1600, ["y"]=500})
table.insert(spawn, {["time"]=12, ["name"]="shooter", ["x"]=1600, ["y"]=400})
table.insert(spawn, {["time"]=13, ["name"]="shooter", ["x"]=1600, ["y"]=450})
table.insert(spawn, {["time"]=14, ["name"]="shooter", ["x"]=1600, ["y"]=450})

table.insert(spawn, {["time"]=16, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=17, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=18, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=19, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=20, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=21, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=22, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})
table.insert(spawn, {["time"]=23, ["name"]="random", ["x"]=1600, ["y"]=math.random(100, 780)})

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