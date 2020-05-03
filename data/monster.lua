function monster_OnStart(id)
    log("Monster started!")
    return 563
end

function monster_OnUpdate(id)
    local hitboxWidth = getEntityWidth(id)
    if hitboxWidth < 1000 then
        setEntityWidth(id, hitboxWidth + 10)
    end
end
