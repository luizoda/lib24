/**
 * Author: Ber 
 * Description: Tortoise and Hare
 * Acha um ciclo com O(1) de memoria em O(n)
 * Util para grafos funcionais implicitos em que vc calcula a resposta localmente 
 * e depois envia a resposta em O(1)
 * https://codeforces.com/gym/102501 (Problema H)
*/

ll m = (1ll<<40);

ll prox(ll a) {
	return (a + (a>>20) + 12345) % m;
}

array<ll, 3> floyd() {

    // retornar a distancia ate o ciclo, inicio do ciclo e tamanho do ciclo
    array<ll, 3> ans = array<ll, 3>();

    // ponto de inicio
    ll slow = 1611516670, fast = 1611516670;

    // primeiro andamos ate que eles se encontrem
    do {
        slow = prox(slow);
        fast = prox(prox(fast));
    } while(slow != fast);


    // depois voltamos um deles para o comeco e andamos ate que eles se encontrem dnv
    slow = 1611516670;
    while (slow != fast) {
        ans[0]++;
        slow = prox(slow);
        fast = prox(fast);
    }

    
    // calcula o tamanho do ciclo
    ans[1] = slow;
    do {
        ans[2]++;
        slow = prox(slow);
    } while (slow != fast);
    return ans;
}