function player_OnStart(id)
    print("Player started!!")
    return 1
end

function player_OnUpdate(id)
    for i=1,10 do
        print("Player updated")
    end
    return 1
end