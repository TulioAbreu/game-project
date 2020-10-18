MONSTER_SPEED = 3;
speed = nil;

entities = {}
-- TODO: One environment per script, so variables dont collide
function OnStart(id)
    log("Monster started!!");
    entities.id = {
        ["speed"] = {
            ["x"] = MONSTER_SPEED * id,
            ["y"] = 0
        }
    };
end

function OnUpdate(id)
    local position = getEntityPosition(id);

    position.x = position.x + speed.x;
    position.y = position.y + speed.y;

    if position.x < -300 or position.x > 300 then
        entities.id.speed.x = entities.id.speed.x * -1;

        if position.x > 300 then
            position.x = 300
        elseif position.x < -300 then
            position.x = -300
        end
    end

    setEntityPosition(id, position);
end
