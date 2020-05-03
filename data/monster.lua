function monster_OnStart(id)
    log("Monster started!")
    return 563
end

function monster_OnUpdate(id)
    setEntityWidth(id, 500)
end
