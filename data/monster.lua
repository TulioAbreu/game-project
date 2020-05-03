local isWalkingLeft = true

function monster_OnStart(id)
    setEntityPositionY(id, -100)
end

function monster_OnUpdate(id)
    local posY = getEntityPositionY(id)
    if isWalkingLeft then
        setEntityPositionY(id, (posY + 30))

        if posY > 300 then
            isWalkingLeft = false
        end
    else
        setEntityPositionY(id, (posY - 30))
        if posY < -300 then
            isWalkingLeft = true
        end
    end
end
