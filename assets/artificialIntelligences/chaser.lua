speed = 350
lastDirection = getElapsedTimeSinceDirection(AI)
playerPosition = getPlayerPosition(AI)
aiPosition = getAIPosition(AI)
directionRate = 4

math.randomseed(os.time())

if lastDirection >= 1 / directionRate and playerPosition["x"] <= aiPosition["x"] then
    local x = -(aiPosition["x"] - playerPosition["x"])
    local y = -(aiPosition["y"] - playerPosition["y"])
    local coef = speed / (math.abs(x) + math.abs(y))

    setDirection(AI, x * coef, y * coef)
end