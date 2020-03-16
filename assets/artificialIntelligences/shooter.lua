speed = 200
bulletSpeed = 400
lastFire = getElapsedTimeSinceFire(AI)
playerPosition = getPlayerPosition(AI)
aiPosition = getAIPosition(AI)
fireRate = 1

math.randomseed(os.time())

if lastFire >= 1 / fireRate and playerPosition["x"] <= aiPosition["x"] then
    local x = -(aiPosition["x"] - playerPosition["x"])
    local y = -(aiPosition["y"] - playerPosition["y"])
    local coef = bulletSpeed / (math.abs(x) + math.abs(y))

    fire(AI, "bullet", x * coef, y * coef)
end

setDirection(AI, -speed, 0)