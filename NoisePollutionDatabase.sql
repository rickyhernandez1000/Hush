-- This table stores data about the WAV recordings and categorizes them based on sound content.
-- Create the WAV database (if it doesn't exist)
CREATE DATABASE IF NOT EXISTS WAV;

-- Use the created database (WAV)
USE WAV;

-- Create a table to store WAV file information
CREATE TABLE Recordings (
  id INT PRIMARY KEY AUTO_INCREMENT,  -- Private Key (auto-increments) for each recording
  file_name VARCHAR(255) NOT NULL,    -- Name of the WAV file (replace with path if storing file path)
  date_time DATETIME NOT NULL,        -- Date and time the recording was made
  location VARCHAR(255) NOT NULL,    -- Description of the recording location (Box # with Street Addy. Ricky can change this if he doesn't want me to hardcode it.)
  unit_number VARCHAR(255),           -- Unit number associated with the recording (optional and might be redundant)
  duration INT NOT NULL,              -- Duration of the recording in seconds
  FOREIGN KEY (file_id) REFERENCES WAV_Files(id)

  -- Categorize sounds based on content (add more categories as needed)
  sound_category ENUM(                -- Use ENUM for predefined categories
    'Construction sounds',
    'Airplanes',
    'Car honks',
    'Highway traffic',
    'Trains',
    'Accidents',
    'Disruptive sounds',
    'Screams',
    'Gun shots',
    'Animal noises',
    'Other'  -- Add an 'Other' category for unclassified sounds
  ) NOT NULL DEFAULT 'Other'
);

-- 
