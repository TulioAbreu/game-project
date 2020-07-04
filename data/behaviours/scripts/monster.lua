local playerId = 0
local monsterSpeed = 3

function monster_OnStart(id)
end

function monster_OnUpdate(id)
    monsterPositionX = getEntityPositionX(id)
    monsterPositionY = getEntityPositionY(id)

    playerPositionX = getEntityPositionX(playerId)
    playerPositionY = getEntityPositionY(playerId)

    newMonsterPositionX = monsterPositionX
    if monsterPositionX < playerPositionX then
        newMonsterPositionX = newMonsterPositionX + monsterSpeed
    end
    if monsterPositionX > playerPositionX then
        newMonsterPositionX = newMonsterPositionX - monsterSpeed
    end

    newMonsterPositionY = monsterPositionY
    if monsterPositionY < playerPositionY then
        newMonsterPositionY = newMonsterPositionY + monsterSpeed
    end
    if monsterPositionY > playerPositionY then
        newMonsterPositionY = newMonsterPositionY - monsterSpeed
    end

    setEntityPositionX(id, newMonsterPositionX)
    setEntityPositionY(id, newMonsterPositionY)
end
