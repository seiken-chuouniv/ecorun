/*
 * Copyright (c) 2013, K. Townsend (microBuilder.eu)
 * https://github.com/microbuilder/
 * All rights reserved.
 *
 * Modified by Yoshio Nakamura, Copyright (c) 2015
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ソースコード形式かバイナリ形式か、変更するかしないかを問わず、以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 * ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、および下記免責条項を含めること。
 * バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の資料に、上記の著作権表示、本条件一覧、および下記免責条項を含めること。
 * 書面による特別の許可なしに、本ソフトウェアから派生した製品の宣伝または販売促進に、<組織>の名前またはコントリビューターの名前を使用してはならない。
 * 本ソフトウェアは、著作権者およびコントリビューターによって「現状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、および特定の目的に対する適合性に関する暗黙の保証も含め、またそれに限定されない、いかなる保証もありません。著作権者もコントリビューターも、事由のいかんを問わず、 損害発生の原因いかんを問わず、かつ責任の根拠が契約であるか厳格責任であるか（過失その他の）不法行為であるかを問わず、仮にそのような損害が発生する可能性を知らされていたとしても、本ソフトウェアの使用によって発生した（代替品または代用サービスの調達、使用の喪失、データの喪失、利益の喪失、業務の中断も含め、またそれに限定されない）直接損害、間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害について、一切責任を負わないものとします。
 */

#include "eeprom.h"

#include <string.h>
#include "eeprom.h"
#include "../cmsis/LPC13Uxx.h"

typedef void (*IAP)(unsigned int[], unsigned int[]);
static const IAP iap_entry = (IAP) 0x1FFF1FF1;

err_t eeprom_write(uint8_t* rom_address, const_buffer buf, uint32_t count)
{
	unsigned int command[5], result[4];
	/* EEPROM Write : IAP Command Code : 61
	 Param 1 : EEPROM address
	 Param 2 : RAM address of data/buffer to write
	 Param 3 : Number of bytes to be written
	 Param 4 : System clock frequency in kHz (SystemCoreClock/1000)
	 Return Codes : 0 - CMD_SUCCESS
	 4 - SRC_ADDR_NOT_MAPPED
	 5 - DST_ADDR_NOT_MAPPED */
	command[0] = 61;
	command[1] = (uint32_t) rom_address;
	command[2] = (uint32_t) buf;
	command[3] = count;
	command[4] = (uint32_t) (SystemCoreClock / 1000);
	/* Invoke IAP call (interrupts need to be disabled during IAP calls)...*/
	__disable_irq();
	iap_entry(command, result);
	__enable_irq();
	if (0 != result[0])
	{
		return EFAULT;
	}
	return 0;
}

err_t eeprom_read(uint8_t* rom_address, buffer buf, uint32_t count)
{
	unsigned int command[5], result[4];
	/* EEPROM Read : IAP Command Code : 62
	 Param 1 : EEPROM address
	 Param 2 : RAM address to store data
	 Param 3 : Number of bytes to read
	 Param 4 : System clock frequency in kHz (SystemCoreClock/1000)
	 Return Codes : 0 - CMD_SUCCESS
	 4 - SRC_ADDR_NOT_MAPPED
	 5 - DST_ADDR_NOT_MAPPED */
	command[0] = 62;
	command[1] = (uint32_t) rom_address;
	command[2] = (uint32_t) buf;
	command[3] = count;
	command[4] = (uint32_t) (SystemCoreClock / 1000);
	/* Invoke IAP call (interrupts need to be disabled during IAP calls)...*/
	__disable_irq();
	iap_entry(command, result);
	__enable_irq();
	if (0 != result[0])
	{
		return EFAULT;
	}
	return 0;
}
