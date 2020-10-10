local PLAYER_SPEED = 10

function player_OnStart(id)
    log('Player started!')
    return 1
end

function player_OnUpdate(id)
    pos = getEntityPosition(id)
    movement = {
        x = 0,
        y = 0
    }

    if getIsKeyPressed("UP") then
        movement["y"] = -PLAYER_SPEED
    end

    if getIsKeyPressed("DOWN") then
        movement["y"] = PLAYER_SPEED
    end

    if getIsKeyPressed("LEFT") then
        movement["x"] = -PLAYER_SPEED
    end

    if getIsKeyPressed("RIGHT") then
        movement["x"] = PLAYER_SPEED
    end

    pos["x"] = pos["x"] + movement["x"]
    pos["y"] = pos["y"] + movement["y"]

    setEntityPosition(id, pos)
end
