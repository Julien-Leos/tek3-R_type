speed = 200
bulletSpeed = 200
lastDirection = getElapsedTimeSinceDirection(AI)
lastFire = getElapsedTimeSinceFire(AI)
playerPosition = getPlayerPosition(AI)
aiPosition = getAIPosition(AI)
aiSize = getAISize(AI)
fireRate = 0.5

math.randomseed(os.time())

if aiPosition["x"] + aiSize["x"] >= 1580 then -- Go Left
    setDirection(AI, -speed, 0)
elseif aiPosition["x"] <= 20 then -- Go Right
    setDirection(AI, speed, 0)
end

if lastFire >= 1 / fireRate then
    fire(AI, "bullet", -(bulletSpeed / 3) * 2, -(bulletSpeed / 3))
    fire(AI, "bullet", -(bulletSpeed / 3), -(bulletSpeed / 3) * 2)
    fire(AI, "bullet", 0, -bulletSpeed)
    fire(AI, "bullet", bulletSpeed / 3, -(bulletSpeed / 3) * 2)
    fire(AI, "bullet", (bulletSpeed / 3) * 2, -(bulletSpeed / 3))
end