-- Clear out all tables
DROP TABLE IF EXISTS `locations`, `moves`, `pokemon`, `categories`, `types`, `regions`;

-- Table for the regions
CREATE TABLE `regions`(
   `id` INT(11) NOT NULL AUTO_INCREMENT,
   `name` VARCHAR(6) NOT NULL,
   PRIMARY KEY (`id`),
   UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB;

-- Fill Regions table
LOCK TABLE `regions` WRITE;
INSERT INTO `regions` VALUES
   (1, "Kanto"), (2, "Johto"), (3, "Hoenn"), 
   (4, "Sinnoh"), (5, "Unova"), (6, "Kalos"), 
   (7, "Alola");
UNLOCK TABLE;

-- Table for the types
CREATE TABLE `types` (
   `id` INT(11) NOT NULL AUTO_INCREMENT,
   `name` VARCHAR(8) NOT NULL,
   PRIMARY KEY(`id`),
   UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB;

-- Fill in the types
LOCK TABLE `types` WRITE;
INSERT INTO `types` VALUES
   (1, "Normal"), (2, "Fighting"),
   (3, "Flying"), (4, "Poison"),
   (5, "Ground"), (6, "Rock"),
   (7, "Bug"), (8, "Ghost"),
   (9, "Fire"), (10, "Water"),
   (11, "Grass"), (12, "Electric"),
   (13, "Ice"), (14, "Psychic"),
   (15, "Dragon"), (16, "Steel"),
   (17, "Dark"), (18, "Fairy");
UNLOCK TABLE;

-- Table for move categories
CREATE TABLE `categories` (
   `id` INT(1) NOT NULL AUTO_INCREMENT,
   `name` VARCHAR(8) NOT NULL,
   PRIMARY KEY (`id`)
) ENGINE=InnoDB;

-- Fill in the categories
LOCK TABLE `categories` WRITE;
INSERT INTO `categories` VALUES
   (1, "Physical"),
   (2, "Special"),
   (3, "Status");
UNLOCK TABLE;

-- Table for Pokemon
CREATE TABLE `pokemon` (
   `id` INT(11) NOT NULL AUTO_INCREMENT,
   `name` VARCHAR(15) NOT NULL,
   `type1` INT(11) NOT NULL,
   `type2` INT(11),
   `hp` INT(3) NOT NULL,
   `atk` INT(3) NOT NULL,
   `def` INT(3) NOT NULL,
   `sp_atk` INT(3) NOT NULL,
   `sp_def` INT(3) NOT NULL,
   `spe` INT(3),
   PRIMARY KEY (`id`),
   UNIQUE KEY `name` (`name`),
   FOREIGN KEY (`type1`) REFERENCES `types`(`id`),
   FOREIGN KEY (`type2`) REFERENCES `types`(`id`) ON DELETE SET NULL
) ENGINE=InnoDB;

-- Add some test pokemon
LOCK TABLE `pokemon` WRITE;
INSERT INTO `pokemon` VALUES
   (25, "Pikachu", 12, NULL, 35, 55, 40, 50, 50, 90),
   (34, "Nidoking", 4, 5, 81, 102, 77, 85, 75, 85);
UNLOCK TABLE;

-- Table for Locations
CREATE TABLE `locations` (
   `rid` INT(11) NOT NULL,
   `pid` INT(11) NOT NULL,
   FOREIGN KEY (`rid`) REFERENCES `regions`(`id`),
   FOREIGN KEY (`pid`) REFERENCES `pokemon`(`id`)
) ENGINE=InnoDB;

-- Table for Moves
CREATE TABLE `moves` (
   `id` INT(11) NOT NULL AUTO_INCREMENT,
   `name` VARCHAR(255) NOT NULL,
   `type1` INT(11) NOT NULL DEFAULT 1,
   `power` INT(3),
   `accuracy` INT(3),
   `category` INT(1) NOT NULL DEFAULT 3,
   PRIMARY KEY (`id`),
   UNIQUE KEY `name` (`name`),
   FOREIGN KEY (`type1`) REFERENCES `types`(`id`),
   FOREIGN KEY (`category`) REFERENCES `categories`(`id`)
) ENGINE=InnoDB;

-- Insert Sample Moves
LOCK TABLE `moves` WRITE;
INSERT INTO `moves` VALUES
   (126, "Fire Blast", 9, 110, 85, 2),
   (392, "Aqua Ring", 10, NULL, NULL, 3),
   (1, "Pound", 1, 40, 100, 1);
UNLOCK TABLE;
