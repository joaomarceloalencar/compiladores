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

function recognize(str::String, aut::DFA)
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

struct NFA <: Automata
    S::Set{Int}
    Σ::Set{Char}
    δ::Dict{Tuple{Int, Char}, Set{Int}}
    S0::Int
    SA::Set{Int}
end

function NFA(states::Vector{Int64}, alphabet::Vector{Char}, 
    transition::Dict{Tuple{Int64, Char}, Set{Int64}}, 
    start::Int64, accepted::Vector{Int64})
    push!(alphabet, 'ϵ')
    NFA(Set(states), Set(alphabet), transition, start, Set(accepted))
end 


function ϵ_closure(states::Set{Int}, aut::NFA)
    new_closure = Set{Int}()
    union!(new_closure, states)
    for transition in keys(aut.δ)
        transition_state = transition[1]
        transition_symbol = transition[2]
        if (transition_state in states && transition_symbol == 'ϵ')
            union!(new_closure, aut.δ[transition])
        end
    end

    if new_closure == states
        return new_closure
    else
        return ϵ_closure(new_closure, aut)
    end

end

function recognize(str::String, aut::NFA)
    # state indicates the current state of the automata. Since this is a NFA, state is a set of states.
    states = ϵ_closure(Set([aut.S0]), aut)
    # processed indicates how much of the input has been read.
    processed = 0 
    str_size = length(str)

    for symbol in str   
        if !(symbol in aut.Σ)
            err = DomainError(symbol, "String contains symbol that does not belong to automata alphabet.")
            throw(err)
            false
        else
            for transition in keys(aut.δ)
                transition_state = transition[1]
                transition_symbol = transition[2]

                println("Current States: ", states, ", ", 
                "Current Symbol: " , symbol, ", ", 
                "Transition: ", transition, "=>", aut.δ[transition])

                if (transition_state in states && transition_symbol == symbol)
                    delete!(states, transition_state)
                    union!(states, ϵ_closure(aut.δ[transition], aut))
                    processed += 1
                    println("New States: ", states)
                end
            end 
        end
    end
    isFinal = false
    reachable_states = ϵ_closure(states, aut)
    println("Reachable States: ", reachable_states)
    for final in aut.SA
        if final in reachable_states
            isFinal = true
            break
        end
    end
    println("Is Final: ", isFinal)
    println("Processed: ", processed)	
    if (isFinal && processed >= str_size)
        true
    else
        if !(isFinal)
            err = DomainError(states, "Final state not reached.")
            throw(err)
        end
        if processed < str_size
            err = DomainError(processed, raw"There are still characters left and no transition to follow.")
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

# NFA - (a|b)c
estados = [0,1,2,3,4]
alfabeto = ['a', 'b', 'c']
funcao_transicao = Dict((0,'a')=>Set([2]), (0,'ϵ')=>Set([1]), 
                        (1,'b')=>Set([3]), 
                        (2,'c')=>Set([4]),
                        (3,'c')=>Set([4]))
inicial = 0
aceitacao = [4]
n1 = NFA(estados, alfabeto, funcao_transicao, inicial, aceitacao)

# NFA - (a|b)*c
estados = [0,1,2,3,4,5,6,7,8,9]
alfabeto = ['a', 'b', 'c']
funcao_transicao = Dict((0,'a')=>Set([1]),  
                        (1,'ϵ')=>Set([2]), 
                        (2,'ϵ')=>Set([3,9]),
                        (3,'ϵ')=>Set([4,6]),
                        (4,'b')=>Set([5]),
                        (5,'ϵ')=>Set([8]),
                        (6,'c')=>Set([7]),
                        (7,'ϵ')=>Set([8]),
                        (8,'ϵ')=>Set([3,9]))
inicial = 0
aceitacao = [9]
n2 = NFA(estados, alfabeto, funcao_transicao, inicial, aceitacao)

# NFA - aa*b
estados = [0,1,2,3]
alfabeto = ['a', 'b']
funcao_transicao = Dict((0,'a')=>Set([0]),
                        (0,'ϵ')=>Set([1]),
                        (1,'a')=>Set([2]),
                        (2,'b')=>Set([3]))
inicial = 0
aceitacao = [3]
n3 = NFA(estados, alfabeto, funcao_transicao, inicial, aceitacao)