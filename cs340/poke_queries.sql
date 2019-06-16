-- Add new Pokemon
insert into pokemon(name, type1, type2, hp, atk, def, sp_atk, sp_def, spe)
   values (:nameInput, :type1Input, :type2Input, :hpInput, :atkInput, :defInput,
         :sp_atkInput, :sp_defInput, speInput);

-- Add new Move
insert into moves(name, type1, power, accuracy, category)
   values (:nameInput, :type1Input, :powerInput, :accuracyInput, :categoryInput);

-- Add new Type
insert into types(name)
   values (:nameInput);

-- Add new Category
insert into categories(name)
   values (:nameInput);

-- Delete Pokemon
delete from pokemon where id=`:toDeleteID`;

-- Delete Move
delete from moves where name=`:toDeleteName`;

-- Delete Type
delete from types where name=`:toDeleteName`;

-- Update Move
update moves
   set power = `:newPowerInput`, accuracy = `:newAccuracyInput`;

-- Update Pokemon
update pokemon   
   set hp=`:newHPInput`, atk=`:newATKInput`, def=`:newDEFInput`, sp_atk=`:newSPATKInput`,
   sp_def=`:newSPDEFInput`, spe=`:newSPEInput`;

-- Show all pokemon
select p.id, p.name, t1.name as `primary type`, t2.name as `secondary type`,
   p.hp, p.atk, p.def, p.sp_atk, p.sp_def, p.spe
   from pokemon p
   inner join types t1 on p.type1 = t1.id
   left join types t2 on p.type2 = t2.id;

-- Show all types
select name from types order by id;

-- Show all moves
select m.name, t.name as `type`, power, accuracy, c.name as `category` from moves m
   inner join categories c on category = c.id
   inner join types t on type1 = t.id;

-- Show searched pokemon
select p.id, p.name, t1.name as `primary type`, t2.name as `secondary type`,
   p.hp, p.atk, p.def, p.sp_atk, p.sp_def, p.spe
   from pokemon p
   inner join types t1 on p.type1 = t1.id
   left join types t2 on p.type2 = t2.id
   where p.id = :idSearch or p.name = :nameSearch;
