### O que é Elang

Semelhante ao processo que o typescript faz, onde converte seu código typescript em javascript, elang converte seu código elang para C++.

A sintax de elang foi inspirada nas linguagens Kotlin e Ruby. Buscando ser o mais simples possível e mantendo uma boa ergonomia.

## Conhecendo o Compilador

Verificando a versão do compilador:

```bash
Linux:
./elang --version

Windows:
.\elang.exe --version
```

Resultado:

	Versão: (C) Elang Compiler v1.0
	Author: Estenio Garcia
	License: Apache 2.0
	Platform: Windows ou Linux

Se este resultado apareceu na sua tela, então está tudo certo com o compilador.

#### Escrevendo 'Hello World' na tela

```swift
print("Hello World!");
```

No terminal, use os seguintes comandos:

	Linux:
	./elang <nome do arquivo>
	
	Windows:
	.\elang.exe <nome do arquivo>

Resultado deve ser:

	success: Compiled Successfully
	Output File..: <nome informado>.cpp
	Elapsed Time.: <tempo decorrido>

Lembrando! Elang é um transpiler. Sendo assim, seu resultado de compilação será um arquivo C++. No caso do exemplo acima, será o nome definido por você ou nome padrão MyApplication.cpp. 

Este arquivo está pronto para ser compilado por um compilador C++ da sua escolha. Vou mostrar exemplos de como compilar o arquivo .cpp com g++ e clang++.

Compilando com Clang++

	clang++ MyApplication -o <nome do aplicativo>

Compilando com G++

	g++ MyApplication -o <nome do aplicativo>

Devo alertar que, para alguns sistemas operacionais, estes compiladores de C++ não vem instalado por padrão, sendo assim, para que você possa utilizá-los, deve ser feita a instalação previamente.

Feito o processo anterior, agora vamos ver o resultado:

No terminal, digite os seguintes comandos:

	Linux:
	./<nome do aplicativo>
	
	Windows:
	.\<nome do aplicativo>.exe

resultado deve ser:

	Hello World!

Aqui você foi apresentado ao projeto e também foi introduzido ao processo de compilação. Agora em diante você será apresentado as demais sintaxes da linguagem.

## Sintaxe da linguagem

Deste tópico em diante lhe será apresentado a sintaxe da linguagem Elang. A apresentação será breve e direta, para que sirva apenas como um guia rápido.

### Declarações de Variáveis

Declarações de variáveis são simples:

```swift
var foo: int;
var bar: float = 33.78;
```

Tipos suportados pelas variáveis:

```swift
var foo: int;
var foo: float;
var foo: bool;
var foo: char;
var foo: string;
```

### Declarações de funções

Seguindo uma strutura similar a delcaração de variáveis, a declaração de função também é simples:

```kotlin
fun:number soma(var:number n1, var:number n2)
   return n1 + n2;
end
```

Tipos suportados pelas funções:

```erlang
fun foo(): int
   # TODO
end

fun foo(): float
   # TODO
end

fun foo(): string
   # TODO
end

fun foo(): bool
   # TODO
end

fun foo(): char
   # TODO
end

fun foo(): void
   # TODO
end
```

Chamando uma função:

```kotlin
var resultado: string = readLine();
print(resultado);
```

### Loop

```ruby
var contador: int = 0;

while(contador < 10) 
  print("Contador: " + intToStr(contador));
  contador = contador + 1;
end
```

### Condicionais

A linguagem suporte apenas um tipo de condicional, sendo a mais conhecida de todos o ```if```, vamos ver como ela é.

```ruby
if(10 > 5)
   print("Viva!");
end
```

```ruby
if((77 + 33) == 100)
   print("hum... algo de errado não está certo!!!");
else
   print("Matemática é confuso!");
end
```

### Convesores de dados

```erlang
floatToStr(float)  # converte dado do tipo float para string
intToStr(int)      # converte dado do tipo integer para string
boolToStr(bool)    # converte dado do tipo boolean para string
floatToInt(float)  # converte dado do tipo float para integer
intToFloat(int)    # converte dado do tipo int para float
strToInt(string)   # converte dado do tipo string para int
strToFloat(string) # converte dado do tipo string para float
strToBool(string)  # converte dado do tipo string para boolean
charToInt(char)    # converte dado do tipo character para integer
charToStr(char)    # converte dado do tipo character para string
```

### Operações de entrada e saída

```kotlin
readLine()     # Lê uma linha no terminal.
readKey()      # Lê uma tecla no terminal.
print(string)  # Escreve uma linha de texto no terminal.
syscmd(string) # Passa comandos para o sistema operacional hospedeiro.
```

## Conclusão

É tudo! Muito obrigado por avaliar o projeto! Sei que não tem o básico como arrays, mas, meu intuito era ter a experiência de desenvolver um linguagem de programação. E este projeto é a prova de que sim eu sou capaz.


