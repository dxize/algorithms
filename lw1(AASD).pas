{
9.  В   текстовом   файле   специальные   термины  выделены
кавычками.  Переписать  файл  так,  чтобы  термины  выделялись
прописными буквами (6).

Среда разработки: Gnu pascal

Текстовый входный файл нужно открывать в кодировке ANSI в фаре

Выполнил: Дмитриев Данил ПС-21
}


PROGRAM MainWords(INPUT, OUTPUT);
VAR
  F1, F2: TEXT;
  NameInputFile, NameOutputFile: STRING;
  Ch: CHAR;

PROCEDURE UpperCaseCh(VAR Ch: CHAR);
BEGIN
  CASE Ch OF
    'a' : Ch := 'A';
    'b' : Ch := 'B';
    'c' : Ch := 'C';
    'd' : Ch := 'D';
    'e' : Ch := 'E';
    'f' : Ch := 'F';
    'g' : Ch := 'G';
    'h' : Ch := 'H';
    'i' : Ch := 'I';
    'j' : Ch := 'J';
    'k' : Ch := 'K';
    'l' : Ch := 'L';
    'm' : Ch := 'M';
    'n' : Ch := 'N';
    'o' : Ch := 'O';
    'p' : Ch := 'P';
    'q' : Ch := 'Q';
    'r' : Ch := 'R';
    's' : Ch := 'S';
    't' : Ch := 'T';
    'u' : Ch := 'U';
    'v' : Ch := 'V';
    'w' : Ch := 'W';
    'x' : Ch := 'X';
    'y' : Ch := 'Y';
    'z' : Ch := 'Z';

    'а' : Ch := 'А';
    'б' : Ch := 'Б';
    'в' : Ch := 'В';
    'г' : Ch := 'Г';
    'д' : Ch := 'Д';
    'е' : Ch := 'Е';
    'ё' : Ch := 'Ё';
    'ж' : Ch := 'Ж';
    'з' : Ch := 'З';
    'и' : Ch := 'И';
    'й' : Ch := 'Й';
    'к' : Ch := 'К';
    'л' : Ch := 'Л';
    'м' : Ch := 'М';
    'н' : Ch := 'Н';
    'о' : Ch := 'О';
    'п' : Ch := 'П';
    'р' : Ch := 'Р';
    'с' : Ch := 'С';
    'т' : Ch := 'Т';
    'у' : Ch := 'У';
    'ф' : Ch := 'Ф';
    'х' : Ch := 'Х';
    'ц' : Ch := 'Ц';
    'ч' : Ch := 'Ч';
    'ш' : Ch := 'Ш';
    'щ' : Ch := 'Щ';
    'ъ' : Ch := 'Ъ';
    'ы' : Ch := 'Ы';
    'ь' : Ch := 'Ь';
    'э' : Ch := 'Э';
    'ю' : Ch := 'Ю';
    'я' : Ch := 'Я'
  ELSE
    WRITE(OUTPUT, 'НЕОБРАБАТЫВАЕМЫЙ СИМВОЛ: ', Ch)
  END
END;

BEGIN
  WRITE('Введите имя входного файла: ');
  READLN(NameInputFile); 

  WRITE('Введите имя выходного файла: ');
  READLN(NameOutputFile);

  ASSIGN(F1, NameInputFile);
  {$I-}  { Отключаем автоматическую обработку ошибок ввода-вывода }
  RESET(F1);
  {$I+}  { Включаем автоматическую обработку ошибок обратно }

  IF IOResult <> 0
  THEN
    BEGIN
      WRITELN('Ошибка открытия входного файла: ', NameInputFile);
      CLOSE(F1);
      EXIT  { Завершаем программу в случае ошибки }
    END;

  ASSIGN(F2, NameOutputFile);
  {$I-}
  REWRITE(F2);
  {$I+}

  IF IOResult <> 0 
  THEN
    BEGIN
      WRITELN('Ошибка открытия выходного файла: ', NameOutputFile);
      CLOSE(F2);
      EXIT
    END;

  WHILE NOT EOF(F1) 
  DO
    BEGIN
      WHILE NOT EOLN(F1) 
      DO
        BEGIN      
          READ(F1, Ch);
          IF Ch <> '"' 
          THEN
            WRITE(F2, Ch)
          ELSE
            BEGIN
              READ(F1, Ch);
              WHILE (Ch <> '"') AND NOT EOLN(F1) 
              DO
                BEGIN
                  UpperCaseCh(Ch);
                  WRITE(F2, Ch);
                  READ(F1, Ch)
                END
            END
        END;
      READLN(F1);
      WRITELN(F2)
    END;

  CLOSE(F1);  { Закрываем входной файл }
  CLOSE(F2);  { Закрываем выходной файл }
END.

