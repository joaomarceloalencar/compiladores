# Vou começar definindo um tipo para autômato. Depois DFA e NFA.
abstract type Automata end

struct DFA <: Automata
    S::Set{Int}
    Σ::Set{Char}
    δ::Dict{Tuple{Int, Char}, Int}
    S0::Int
    SA::Set{Int}
end

function DFA(states::Vector{Int64}, alphabet::Vector{Char}, 
    transition::Dict{Tuple{Int64, Char}, Int64}, 
    start::Int64, accepted::Vector{Int64})

    DFA(Set(states), Set(alphabet), transition, start, Set(accepted))
end    

struct NFA <: Automata
    S::Set{Int}
    Σ::Set{Char}
    δ::Dict{Tuple{Int, Char}, Set{Int}}
    S0::Int
    SA::Set{Int}
end

function NFA(states::Vector{Int64}, alphabet::Vector{Char}, 
    transition::Dict{Tuple{Int64, Char}, Int64}, 
    start::Int64, accepted::Vector{Int64})
    push!(alphabet, 'ϵ')
    DFA(Set(states), Set(alphabet), transition, start, Set(accepted))
end 

function recognize(str::String, aut::Automata)
    state = aut.S0
    str_size = length(str)
    processed = 0 
    for symbol in str
        if !(symbol in aut.Σ)
            err = DomainError(symbol, "String contains symbol that does not belong to automata alphabet.")
            throw(err)
            false
        else
            for transition in keys(aut.δ)
                transition_state = transition[1]
                transition_symbol = transition[2]
                if (symbol == transition_symbol && state == transition_state)    
                    println("Current State: ", state, ", ", 
                        "Current Symbol: " , symbol, ", ", 
                        "Transition: ", transition, ", ",
                        "New State:", aut.δ[transition])
                    state = aut.δ[transition]
                    processed += 1
                    break
                end
            end    
        end
    end
    if (state in aut.SA && processed == str_size)
        true
    else
        if processed < str_size
            err = DomainError(processed, "There are still characters left and no transition to follow.")
            throw(err)
        end
        false 
    end
end 

# Autômatos de testes
# DFA - a*(b|c)
estados = [0,1]
alfabeto = ['a', 'b', 'c']
funcao_transicao = Dict((0,'a')=>0, (0,'b')=>1, (0,'c')=>1)
inicial = 0
aceitacao = [1]
d1 = DFA(estados, alfabeto, funcao_transicao, inicial, aceitacao)

# DFA - a(b|c)*
estados = [0,1,2,3]
alfabeto = ['a', 'b', 'c']
funcao_transicao = Dict((0,'a')=>1, 
                        (1,'b')=>2, (1,'c')=>3, 
                        (2,'b')=>2, (2,'c')=>3, 
                        (3,'c')=>3, (3,'b')=>2)
inicial = 0
aceitacao = [1,2,3]
d2 = DFA(estados, alfabeto, funcao_transicao, inicial, aceitacao)