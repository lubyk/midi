/*
  ==============================================================================

   This file is part of the LUBYK project (http://lubyk.org)
   Copyright (c) 2007-2011 by Gaspard Bucher (http://teti.ch).

  ------------------------------------------------------------------------------

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

  ==============================================================================
*/
#ifndef LUBYK_INCLUDE_MIDI_OUT_H_
#define LUBYK_INCLUDE_MIDI_OUT_H_

#include "RtMidi.h"

namespace midi {
/** This class lets you send midi events through virtual ports (where possible)
 * or connect to midi receivers.
 *
 * @dub push: pushobject
 *      register: Out_core
 *      string_format:'%%s (%%f)'
 *      string_args:'self->portName(), self->port()'
 */
class Out : public dub::Thread {
public:
  Out()
     : port_id_(-1)
     , port_name_("lubyk")
     , midi_out_(NULL)
     , buffer_(3, 0) {
    midi_out_ = new RtMidiOut;
  }

  ~Out() {
    if (midi_out_) {
      delete midi_out_;
    }
  }

  int port() const {
    return port_id_;
  }

  const char *portName() const {
    return port_name_.c_str();
  }

  void openPort(int port, lua_State *L) {
    if (midi_out_ == NULL) {
      lua_pushstring(L, "RtMidiOut not initialized: cannot open port.");
      lua_error(L);
    }
    midi_out_->closePort();

    if (port == -1) {
      // create a virtual port
      midi_out_->openVirtualPort(port_name_);
    } else {
      // try to connect to the given port
      midi_out_->openPort(port);
      port_name_ = midi_out_->getPortName(port);
    }
    port_id_ = port;
  }

  void openPort(const char *port_name, lua_State *L) {
    // 1. find port from given name
    int port_count = midi_out_->getPortCount();
    std::string name;

    for (int i = 0; i < port_count; ++i) {
      name = midi_out_->getPortName(i);
      if (name == port_name) {
        return openPort(i, L);
      }
    }
    lua_pushfstring(L, "Port '%s' not found.", port_name);
    lua_error(L);
  }

  void virtualPort(const char *port_name, lua_State *L) {
    port_name_ = port_name;
    return openPort(-1, L);
  }

  void send(int a, int b, int c) {
    if (!midi_out_) return;
    buffer_[0] = a;
    buffer_[1] = b;
    buffer_[2] = c;
    midi_out_->sendMessage(&buffer_);
  }

  /** List of midi output ports.
   */
  static LuaStackSize ports(lua_State * L) {
    RtMidiIn midi_in;
    int count = midi_in.getPortCount();
    lua_newtable(L);
    int tp = lua_gettop(L);
    for(int i = 0; i < count; ++i) {
      std::string name = midi_in.getPortName(i);
      lua_pushlstring(L, name.c_str(), name.length());
      lua_rawseti(L, tp, i + 1);
    }
    return 1;
  }
private:

  /** Midi port id to which the element is connected.
   *  If the value is -1 this means it has opened its own virtual port.
   */
  int port_id_;

  /** The connected port name.
   */
  std::string port_name_;

  /** Pointer to our RtMidiOut instance (midi::Out is just a wrapper around
   *  RtMidiOut).
   */
  RtMidiOut *midi_out_;

  /** Message sending buffer.
   * TODO: modify RtMidiOut so we do not need this.
   */
  std::vector<unsigned char> buffer_;
};

} // midi

#endif // LUBYK_INCLUDE_MIDI_OUT_H_
#if 0
/*
   ==============================================================================

   This file is part of the LUBYK project (http://lubyk.org)
   Copyright (c) 2007-2010 by Gaspard Bucher - Buma (http://teti.ch).

   ------------------------------------------------------------------------------

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

   ==============================================================================
 */
#include "lubyk.h"
using namespace rk;

#include "Midi/RtMidi.h"

/** This class lets you create virtual ports (where possible) or connect
 * to midi receivers and send them midi data.
 */
class MidiOut : public Node {
 public:
  MidiOut() : port_id_(-1), midi_out_(NULL) {
    set_is_ok(false);  // port not opened
    try {
      midi_out_ = new RtMidiOut;
    } catch (RtError &error) {
      midi_out_ = NULL;
      error_.set(UNKNOWN_ERROR, error.getMessageString());
    }
  }

  virtual ~MidiOut() {
    if (midi_out_) {
      delete midi_out_;
    }
  }

  const Value init () {
    Node::init();

    if (error_.is_error()) {
      return error_;
    } else if (!is_ok()) {
      return openPort(port_id_);
    } else {
      return gNilValue;
    }
  }

  // [1] Send midi data out
  const Value midi(const Value &val) {
    MidiMessage *msg;

    if (!is_ok() || !val.is_midi()) return MidiValue();

    msg = val.midi_message_;

    if (msg->wait() > 0) {
      bang_me_in(msg->wait(), val);
    } else {
      // send now
      bang(val);
    }

    return val;
  }

  // [2] Get/set midi out port
  const Value port(const Value &val) {
    if (val.is_real()) {
      return openPort(val.r);
    } else if (val.is_string()) {
      if (midi_out_ == NULL) return error_;
      // 1. find port
      size_t port_count = midi_out_->getPortCount();
      std::string name;

      for (size_t i = 0; i < port_count; ++i) {
        try {
          name = midi_out_->getPortName(i);
          if (val.str() == name) {
            return openPort(i);
          }
        } catch (RtError &error) {
          error_.set(UNKNOWN_ERROR, error.getMessageString());
          return error_;
        }
      }
    }
    return port_id_ == -1 ? Value(name_) : Value(port_id_);
  }

  /** internal use to send NoteOff or delayed NoteOn.
   */
  virtual void bang(const Value &val) {
    const MidiMessage *msg = val.midi_message_;
    midi_out_->sendMessage( &(msg->data()) );
    if (msg->type() == NoteOn && msg->length() > 0) {
      Value out(msg); // copy
      out.midi_message_->note_on_to_off();
      bang_me_in(msg->length(), out, true);
    }
  }

  // void clear() {
  //   remove_my_events();
  // }
  //
  // // print a list of possible outputs
  // static void list(std::ostream * pOutput, const Value &p)
  // {
  //   std::vector<std::string> ports;
  //   if (!output_list(pOutput, ports)) return;
  //   size_t nPorts = ports.size();
  //
  //   *pOutput << "Midi out ports (" << nPorts << "):" << std::endl;
  //
  //   for (size_t i=0; i<nPorts; i++ ) {
  //     *pOutput << "  " << i << ": " << ports[i] << std::endl;
  //   }
  // }

  virtual void inspect(Value *hash) const {
    if (is_ok() && port_id_ >= 0) {
      std::string name;
      try {
        name = midi_out_->getPortName(port_id_);
        hash->set("port", name);
      } catch (RtError &error) {
        hash->set("port", error.getMessageString());
      }
    } else if (is_ok()) {
      hash->set("port", name_);
    } else {
      hash->set("port", "--");
    }
  }
private:
  const Value openPort(int port) {
    if (midi_out_ == NULL) return error_;
    midi_out_->closePort();
    set_is_ok(false);

    if (port == -1) {
      // create a virtual port
      try {
        midi_out_->openVirtualPort(name_);
      } catch (RtError &error) {
        return error_.set(UNKNOWN_ERROR, error.getMessageString());
      }
    } else {
      // try to connect to the given port
      try {
        midi_out_->openPort( port );
      } catch (RtError &error) {
        return error_.set(UNKNOWN_ERROR, error.getMessageString());
      }
    }
    port_id_ = port;
    set_is_ok(true);
    return Value(port_id_);
  }

  // static bool output_list(std::ostream * pOutput, std::vector<std::string>& ports)
  // {
  //   RtMidiOut *midiout = 0;
  //   unsigned int i,nPorts;
  //   std::string portName;
  //
  //   try {
  //     midiout = new RtMidiOut();
  //   }
  //   catch (RtError &error) {
  //     *pOutput << error.getMessageString() << std::endl;
  //     return false;
  //   }
  //
  //   ports.clear();
  //
  //   nPorts = midiout->getPortCount();
  //
  //   for ( i=0; i<nPorts; i++ ) {
  //     try {
  //       portName = midiout->getPortName(i);
  //       ports.push_back(portName);
  //     } catch (RtError &error) {
  //       *pOutput << error.getMessageString() << std::endl;
  //       return false;
  //     }
  //   }
  //   return true;
  // }

  /** Midi port id to which the element is connected.
   *  If the value is -1 this means it has opened its own virtual port.
   */
  int port_id_;

  /** Pointer to our RtMidiOut instance (MidiOut is just a wrapper around
   *  RtMidiOut).
   */
  RtMidiOut * midi_out_;

  /** ErrorValue to store the error message that can occur during
   *  object construction.
   */
  Value error_;
};

extern "C" void init(Planet &planet) {
  CLASS(MidiOut, "Port to send midi values out. If no port is provided, tries to open a virtual port.", "port: [port number/name]")
  // TODO: this should be a SelectIO...
  METHOD(MidiOut, midi, Oscit::midi_io("Received values are sent out to the current midi port."))
  METHOD(MidiOut, port, Oscit::any_io("Port number or string."))
  // CLASS_METHOD(MidiOut, list)
  // METHOD(MidiOut, clear)
}

#endif
