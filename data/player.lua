local PLAYER_SPEED = 10

function player_OnStart(id)
    log('Player started!')
    return 1
end

function player_OnUpdate(id)
    local position = {
        x = getEntityPositionX(id),
        y = getEntityPositionY(id)
    }

    if getIsKeyPressed('UP') then
        setEntityPositionY(id, position.y-PLAYER_SPEED)
    end

    if getIsKeyPressed('DOWN') then
        setEntityPositionY(id, position.y+PLAYER_SPEED)
    end

    if getIsKeyPressed('LEFT') then
        setEntityPositionX(id, position.x-PLAYER_SPEED)
    end

    if getIsKeyPressed('RIGHT') then
        setEntityPositionX(id, position.x+PLAYER_SPEED)
    end
end