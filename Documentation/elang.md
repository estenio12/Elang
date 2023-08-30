### O que é Elang

Semelhante ao processo que o typescript faz, onde converte seu código typescript em javascript, elang converte seu código elang para C++.

A sintax de elang foi inspirada em linguagens como Ruby, Kotlin e python entre outras. Buscando ser o mais simples possível e mantendo uma boa ergonomia.

## Conhecendo o Compilador

Verificando a versão do compilador:

```bash
Linux:
./elangc --version

Windows:
.\elangc.exe --version
```

Resultado:

	Versão: (C) Elang Compiler v1.0
	License: Apache 2.0
	Author: Estenio Garcia

Se este resultado apareceu na sua tela, então está tudo certo com o compilador, e podemos então dar início as explicações de como usar.

#### Escrevendo 'Hello World' na tela

```swift
print("Hello World!");
```

Simples! Não? Agora vamos compilar este código.

No terminal, basta usar os seguintes comandos:

	Linux:
	./elangc <nome do arquivo>
	
	Windows:
	.\elangc.exe <nome do arquivo>

Resultado deve ser:

	Compile Finished
	Output File Name: MyApplication
	Target Platform: <nome do sistema operacional>
	Time Elapsed: <tempo decorrido>

Lembrando! Elang é um transpiler. Sendo assim, seu resultado de compilação será um arquivo C++. No caso do exemplo acima, será MyApplication.cpp. 

Este arquivo está pronto para ser compilado por um compilador C++ da sua escolha. Vou mostrar exemplos de como compilar o arquivo .cpp com G++ e Clang++.

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

## Sintaxes da linguagem

Deste tópico em diante lhe será apresentado as sintaxes disponíveis para linguagem Elang. A apresentação será breve e direta, para que sirva apenas como um guia rápido.

### Declarações de Variáveis

A forma para declarar variáveis na linguagem é bem simples. Sendo apenas por:

```swift
# esta é uma variável numérica, que pode ser inteira ou fracionada
var:number foo;
```

Tipos suportados pelas variáveis:

```swift
var:number foo;
var:text foo;
var:bool foo;
var:char foo;
```

Variáveis inicializadas:

```swift
var:number foo = 10 | 10.5;
var:text foo = "Hello World";
var:bool foo = true | false;
var:char foo = 'P';
```

### Declarações de funções

Seguindo uma strutura similar a delcaração de variáveis, a declaração de função também é simples:

```kotlin
fun:number soma(var:number n1, var:number n2)
	return n1 + n2;
end
```

Tipos suportados pelas funções:

```kotlin
fun:number foo() end
fun:text foo() end
fun:bool foo() end
fun:char foo() end
fun:void foo() end
```

Chamando a função criada:

```kotlin
var:text resultado = numberToText(soma(10, 10));
print(resultado);
```

Após executar processo de compilação já apresentado anteriormente, ao executar o aplicativo o resultado deve ser:

	20

### Loops

```kotlin
while() end
for() end
```

Exemplos:

While:

```kotlin
var:number contador = 0;

while(contador < 10) 
	print(numberToText(contador));
	contador = contador + 1;
end
```

For:

```kotlin
for(in 10) 
	print(numberToText(index));
end
```

O for tem duas opções para interação, sendo elas: ```in``` ou ```at```. No exemplo acima usamos o ```in```, agora vamos ver o mesmo exemplo com o ```at```.

```kotlin
for(at 10) 
	print(numberToText(index));
end
```

A grande diferença entre os dois é que o ```in``` vai de 0 até um digito antes do limite, exemplo: 

```in``` 10 = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

Já o ```at``` vai de 0 até o valor limite, exemplo: 

```at``` 10 = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 

A variável ```index``` é exclusiva do loop-for, nesse caso, você consiguirá utilizá-lo quando dentro do mesmo. Ela armazena o número de vezes que o loop já executou.

### Condicionais

A linguagem suporte apenas um tipo de condicional, sendo a mais conhecida de todos o ```if```, vamos ver como ela é.

```kotlin
if(10 > 5)
	print("Viva!");
end
```

```kotlin
if((77 + 33) == 100)
	print("hum... algo de errado não está certo!!!");
else
	print("Matemática é confuso!");
end
```

### Convesores de dados

```kotlin
numberToText(number) # Converte número para texto(string).
numberToChar(number) # Converte número para carácter.
numberToBool(number) # Converte número para booleano.

charToNumber(char) # Converte carácter para número.
charToText(char) # Converte carácter para texto(string).
charToBool(char) # Converte carácter para booleano.

boolToNumber(bool) # Converte booleano para número.
boolToText(bool) # Converte booleano para texto(string).
boolToChar(bool) # Converte booleano para carácter.

textToNumber(text) # Converte texto para número.
textToBool(text) # Converte texto para booleano.
textToChar(text) # Converte texto para carácter.
```

### Operações de entrada e saída

```kotlin
readline() # Lê uma linha do console.
readword() # Lê uma palavra do console.
readchar() # Lê uma letra do console.
print(text) # Escreve texto no console.
sysexec(text) # Passa comandos para o sistema operacional hospedeiro.
```

## Conclusão

É tudo! Muito obrigado por avaliar o projeto! Sei que não tem o básico como arrays, mas, meu intuito era ter a experiência de desenvolver um linguagem de programação. E este projeto é a prova de que sim eu sou capaz.


