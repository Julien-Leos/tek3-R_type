speed = 100
bulletSpeed = 300
lastDirection = getElapsedTimeSinceDirection(AI)
lastFire = getElapsedTimeSinceFire(AI)
fireRate = 1
directionRate = 0.5

math.randomseed(os.time())

if lastDirection >= 1 / directionRate then
    local rand = math.random(-speed / 2, speed / 2)

    setDirection(AI, -(speed - rand), rand)
end

if lastFire >= 1 / fireRate then
    local rand = math.random(-bulletSpeed, bulletSpeed)
    local abs = math.abs(rand)

    fire(AI, "bullet", -(bulletSpeed - abs), rand)
end