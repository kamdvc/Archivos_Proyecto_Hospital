USE hospital1;
CREATE TABLE paciente (
    codigo_historia_clinica int primary key,
    nombre_paciente VARCHAR(40) NOT NULL,
    apellido_paciente VARCHAR(40) NOT NULL,
    telefono VARCHAR(40) NOT NULL,
    sexo VARCHAR(1) NOT NULL,
    ciudad VARCHAR(40) NOT NULL,
    documento_identidad VARCHAR(40) NOT NULL

);

CREATE TABLE medico (
    codigo_medico int primary key,
    nombre VARCHAR(40) NOT NULL,
    apellido VARCHAR(40) NOT NULL,
    especialidad VARCHAR(40) NOT NULL,
    tarjeta_profesional VARCHAR(40) NOT NULL
);

CREATE TABLE ingreso (
    codigo_ingreso int primary key,
    codigo_historia_clinica int,
    codigo_medico int,
    fecha_ingreso VARCHAR(40) NOT NULL,
    no_piso VARCHAR(40) NOT NULL,
    no_cama VARCHAR(40) NOT NULL,
    diagnostico VARCHAR(40) NOT NULL,
    costo_tratamiento VARCHAR(40) NOT NULL,
    FOREIGN KEY (codigo_historia_clinica) REFERENCES paciente(codigo_historia_clinica),
    FOREIGN KEY (codigo_medico) REFERENCES medico(codigo_medico)
);


INSERT INTO paciente (codigo_historia_clinica, nombre_paciente, apellido_paciente, telefono, sexo, ciudad, documento_identidad) VALUES
(1, 'Juan', 'Gomez', 5551234, 'M', 'El Progreso', 123456789),
(2, 'María', 'López', 5555678, 'F', 'Zacapa', 987654321),
(3, 'Pedro', 'Martínez', 5558765, 'M', 'Ciudad Capital', 456789012),
(4, 'Laura', 'Pérez', 5554321, 'F', 'Chiquimula', 789012345),
(5, 'Carlos', 'Sánchez', 5559876, 'M', 'Peten', 321098765);

INSERT INTO medico (codigo_medico, nombre, apellido, especialidad, tarjeta_profesional) VALUES
(1, 'Dr. Rodríguez', 'Pérez', 'Cardiología', 123456),
(2, 'Dra. Gómez', 'López', 'Pediatría', 654321),
(3, 'Dr. Martínez', 'Gómez', 'Cirugía', 987654),
(4, 'Dra. Sánchez', 'Fernández', 'Dermatología', 456789),
(5, 'Dr. Pérez', 'García', 'Neurología', 789012);

INSERT INTO ingreso (codigo_ingreso, codigo_historia_clinica, codigo_medico, fecha_ingreso, no_piso, no_cama, diagnostico, costo_tratamiento) VALUES
(1, 1, 1, '2023-01-01', '2', '101', 'Problemas cardíacos', '5000'),
(2, 2, 2, '2023-02-15', '3', '202', 'Gripe', '1000'),
(3, 3, 3, '2023-03-10', '1', '303', 'Apéndice inflamado', '8000'),
(4, 4, 4, '2023-04-20', '2', '404', 'Dermatitis', '2000'),
(5, 5, 5, '2023-05-05', '3', '505', 'Migraña', '3000');

select*from paciente;
select*from medico;
select*from ingreso;
